delphi-cpp
=========

DelphiCpp is a collection of tools allowing for the creation of copora of C/C++ packages with specific desired features. Features can range from API usage, to language features, to just about anything that can be detected with static analysis. We provide three containerized tools for this:

1. A scraper that goes through ConanCenter to get C/C++ packages
2. A tool for creating a mapping from packages to features of those packages using easily extendable queries
3. A tool for filtering this feature map to obtain the set of packages with just the desired features

## General Usage

DelphiCpp is used through Docker containers. To build the necessary images, clone this repo, `cd` into its top level directory, and then run

```docker build . -t YOUR_NAME -f ./dockerfiles/{dcpp_scrape, dcpp_extract, dcpp_filter}.Dockerfile```

### Reminder on Binding Single File Volumes
Make sure you `touch` files before binding them into the container - even if they're files used for container output. Otherwise, Docker will create it, but as a directory, which will cause the container to fail.

### General Usage for One Container
```docker run -v {bind_1} -v {bind_2} ... dcpp_{scrape, extract, filter} --flag-1 arg1 ...```

### `dcpp_scrape` usage
This container allows you to scrape C/C++ packages from ConanCenter. You can provide the number of packages you want to scrape.

#### Volumes
- packages output: `-v ./path/to/local/dir/:/volumes/packages/`
- log file output: `-v ./path/to/file.log:/volumes/log.log`

#### Command-Line Options
- `--num-packages/-n {NUMBER OF PACKAGES TO SCRAPE}`

### `dcpp_extract` usage
This container runs the desired queries over the scraped packages and constructs a map from packages to the features they contain. There are also various configuration options related to performance.

#### Volumes
- packages input: `-v ./path/to/packages/dir/:/volumes/packages/`
- configuration input: `-v ./path/to/config.json:/volumes/config.json`
- feature map output: `-v ./path/to/ftr_map.json:/volumes/ftr_map.json`
- log directory output: `-v ./path/to/log/dir/:/volumes/logs/`

#### Command-Line Options
- `--chunk-size/-cs {HOW MANY PACKAGES TO PROCESS AT A TIME}`
- `--max-bins/-mb {MAX NUMBER OF BINARIES A PACKAGE CAN HAVE}`
- `--timeout/-t {TIMEOUT (IN MINUTES) FOR ANALYZING A PACKAGE}`

### `dcpp_filter` usage
This container, given a feature map and a list of filters, outputs the packages matching the list of features.

#### Volumes
- feature map input: `-v ./path/to/ftr_map.json:/volumes/ftr_map.json`
- filters input: `-v ./path/to/filters.json:/volumes/filters.json`
- filtered results output: `-v ./path/to/results.json:/volumes/fltrd_map.json`
- log file output: `-v ./path/to/file.log:/volumes/log.log`

## File Formats

### `dcpp_extract` Configuration File
This is a json configuration file which specifies the queries to be run. This is its format:
```
[
    "Query1Name",
    "Query2Name",
    ...
]
```

### `dcpp_filter` Filters File
The filters file is a JSON file consisting of an array of filters, where each filter is an object in the following form:
```
{
    "feature_id": {
        "name": "LongestInheritanceChainQuery",
        "type": "cpp",
        "attr_type": "uint",
        "data_type": "binmap"
    },
    "use_range": true,
    "filter_type": "exists",
    "range": {
        "attr_type": "uint",
        "lower_bound": 2,
        "upper_bound": 5
    }
}
```
If `use_range` is set to `false`, then `filter_type` and `range` need not be included. The options for `filter_type` are:
- `exists`: one binary in the binary map has to fulfill the range
- `forall`: all binaries in the binary map have to fulfill the range
- `one_attr`: the feature only has one attribute for the entire package instead of a binary map
- `no_attr`: the feature has no attached data

If `attr_type` is `uint` or `float`, then `range` includes a `lower_bound` and `upper_bound`, as above. In all other cases, those two keys are replaced with a singular one named `val`.

## Current Queries and the Features They Derive

### `IsExecQuery`
This query goes through each binary and determines whether it is an executable or not. It derives one feature with the following ID:
```
{
    "name": "IsExecQuery",
    "type": "unit",
    "attr_type": "bool",
    "data_type": "binmap"
}
```

### `NumInstructionsQuery`
This query finds the number of LLVM instructions per binary. It derives one feature with the following ID:
```
{
    "name": "NumInstructionsQuery",
    "type": "unit",
    "attr_type": "bool",
    "data_type": "binmap"
}
```

### `LongestInheritanceChainQuery`
This query goes through a package and determines conservatively whether it came (at least partially) from C++ source code. If so, it finds the longest depth of the inheritance tree for each binary in the package. It derives two features with the following IDs:
```
{
    "name": "LongestInheritanceChainQuery",
    "type": "notcpp",
    "attr_type": "unit",
    "data_type": "unit"
},
{
    "name": "LongestInheritanceChainQuery",
    "type": "cpp",
    "attr_type": "uint",
    "data_type": "binmap"
}
```

### `CallGraphSizeQuery`
This query goes through each binary and determines the call graph size in terms of the number of nodes and edges. It derives two features with the following IDs:
```
{
    "name": "CallGraphSizeQuery",
    "type": "node",
    "attr_type": "uint",
    "data_type": "binmap"
},
{
    "name": "CallGraphSizeQuery",
    "type": "edge",
    "attr_type": "uint",
    "data_type": "binmap"
}
```

## Adding New Queries

To add a new query, it's just a matter of adding two source code files, `src/core/queries/your_query.{hpp, cpp}`. In them, you have to define a new class which extends the `Core::Query` interface. Look to the other queries as examples of what to do. In the `.cpp` file, in the top level namespace, write the line
```
REGISTER_QUERY(YourQueryClassName)
```
This will allow DelphiCpp to know about the Query when you compile it.
