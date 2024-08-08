class A {
  public:
  virtual void foo() { }
  virtual ~A() {}
};

class B : virtual public A {
  public:
  void foo() override { }
  ~B() override {}
};

class C : virtual public A{
  public:
  void foo() override { }
  ~C() override {}
};

class D : virtual public B, virtual public C {
  public:
  void foo() override { }
  ~D() override {}
};

class E : virtual public D {
  public:
  void foo() override { }
  ~E() override {}
};

class F {
  public:
  virtual void foo() { }
  virtual ~F() {}
};

class G : virtual public F {
  public:
  void foo() override { }
  ~G() override {}
};

class H : virtual public G {
  public:
  void foo() override { }
  ~H() override {}
};

int main() {
  A *thing1 = new C();
  B *thing2 = new B();
  C *thing3 = new D();
  C *thing4 = new E();
  F *thing5 = new G();
  F *thing6 = new H();

  thing1->foo();
  thing2->foo();
  thing3->foo();
  thing4->foo();
  thing5->foo();
  thing6->foo();

  delete thing6;
  delete thing5;
  delete thing4;
  delete thing3;
  delete thing2;
  delete thing1;
}