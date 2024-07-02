import os, sqlite3
from logging import Logger
from sqlite3 import Connection

class ConanCache:

  def __init__(self, cache_path: str, logger: Logger):
    self.__cache_path = cache_path
    self.__logger = logger
    self.__connection: Connection | None = None
  
  def __del__(self):
    self.close_conn()
  
  # returns (bin_dir: str, conan_reference: str)
  def get_package_info(self, recipe: str, version: str) -> tuple[str, str] | None:
    """Gets the directory where all of the binaries are stored."""
    if not self.__update_connection():
      return None
    
    cur = self.__connection.cursor()

    recipe_ref = f'{recipe}/{version}'
    res = cur.execute("""SELECT path, rrev, pkgid FROM packages 
                            WHERE reference=?
                            ORDER BY timestamp DESC""", (recipe_ref,)).fetchone()
    
    if res is None:
      # dump existing references if we can't find recipe_ref
      self.__logger.debug(f'ConanCache: current references in `cache.sqlite3`:\n\t\t{'\n\t\t'.join(cur.execute('SELECT reference FROM packages').fetchall())}')
      self.__logger.warning(f'ConanCache: cannot find `{recipe_ref}` in local conan cache database')
      return None

    (rel_path, rrev, pkgid) = res
    bin_dir = os.path.join(os.path.split(self.__cache_path)[0], rel_path, 'p')

    if not os.path.isdir(bin_dir):
      self.__logger.warning(f'ConanCache: cannot find installation directory for {recipe_ref}: `{bin_dir}`')
      return None
    
    reference = f'{recipe}/{version}*#{rrev}:{pkgid}'
    print(reference)
    return (bin_dir, reference)
  
  def get_package_set(self) -> set[str] | None:
    if not self.__update_connection():
      return None
    
    cur = self.__connection.cursor()
    res = cur.execute("""SELECT reference FROM packages""")

    if res is None:
      return set()

    return set(map(lambda x: x[0], res.fetchall()))


  def cache_file_exists(self) -> bool:
    return os.path.isfile(self.__cache_path)
  
  def close_conn(self):
    if self.__connection is not None and self.cache_file_exists():
      self.__connection.close()
    self.__connection = None
  
  def __update_connection(self) -> bool:
    match (self.__connection, self.cache_file_exists()):
      case (None, True):
        self.__connection = sqlite3.connect(self.__cache_path)
        return True
      case (None, False):
        self.__logger.debug(f'ConanCache: unable to find cache file at: {self.__cache_path}')
        return False
      case (_, True):
        return True
      case (_, False):
        self.__logger.warning(f'ConanCache: cache file at `{self.__cache_path}` unexpectedly disappeared while still connected.')
        self.__connection = None
        return False