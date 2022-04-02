#ifndef FACTORY_METHOD_H
#define FACTORY_METHOD_H

#include <iostream>
#include <strings.h>
#include <string.h>

using namespace std;

/**
 * The Product interface declares the operations that all concrete products must
 * implement.
 */
class Product
{
public:
    virtual ~Product() {}
    virtual std::string Operation() const = 0;
};

/**
 * Concrete Products provide various implementations of the Product interface.
 */
class ConcreteProduct1 : public Product
{
public:
    std::string Operation() const override{
        return "{Result of the ConcreteProduct1}";
    }
};

class ConcreteProduct2 : public Product
{
public:
    std::string Operation() const override{
        return "{Result of the ConcreteProduct2}";
    }
};

/**
 * The Creator class declares the factory method that is supposed to return an
 * object of a Product class. The Creator's subclasses usually provide the
 * implementation of this method.
 */

class Creator
{
    /**
     * Note that the Creator may also provide some default implementation of the
     * factory method.
     */
public:
    virtual ~Creator(){};
    virtual Product *FactoryMethod() const = 0;
    /**
     * Also note that, despite its name, the Creator's primary responsibility is
     * not creating products. Usually, it contains some core business logic that
     * relies on Product objects, returned by the factory method. Subclasses can
     * indirectly change that business logic by overriding the factory method and
     * returning a different type of product from it.
     * 还要注意的是，尽管名称不同，创造者的主要责任不是创造产品。
     * 通常，它包含一些依赖于工厂方法返回的产品对象的核心业务逻辑。
     * 子类可以通过重写factory方法并从中返回不同类型的产品来间接更改该业务逻辑
     */

    std::string SomeOperation() const{
        // Call the factory method to create a Product object.
        Product *product = this->FactoryMethod();
        // Now, use the product.
        std::string result = "Creator: The same creator's code has just worked with " + product->Operation();
        delete product;
        return result;
    }
};

/**
 * Concrete Creators override the factory method in order to change the
 * resulting product's type.
 */
class ConcreteCreator1 : public Creator
{
    /**
     * Note that the signature of the method still uses the abstract product type,
     * even though the concrete product is actually returned from the method. This
     * way the Creator can stay independent of concrete product classes.
     */
public:
    Product *FactoryMethod() const override{
        return new ConcreteProduct1();
    }
};

class ConcreteCreator2 : public Creator
{
public:
    Product *FactoryMethod() const override{
        return new ConcreteProduct2();
    }
};

/**
 * The client code works with an instance of a concrete creator, albeit through
 * its base interface. As long as the client keeps working with the creator via
 * the base interface, you can pass it any creator's subclass.
 */
void ClientCode(const Creator &creator)
{
    std::cout << "Client: I'm not aware of the creator's class, but it still works.\n"
              << creator.SomeOperation() << std::endl;
}

/**
 * The Application picks a creator's type depending on the configuration or
 * environment.
 */
int MainFactoryMethod()
{
    std::cout << "App: Launched with the ConcreteCreator1.\n";
    Creator *creator = new ConcreteCreator1();                   //
    ClientCode(*creator);
    std::cout << std::endl;
    std::cout << "App: Launched with the ConcreteCreator2.\n";
    Creator *creator2 = new ConcreteCreator2();
    ClientCode(*creator2);

    delete creator;
    delete creator2;
    return 0;
}

#endif //!FACTORY_MOTHOD_H
/*-----------------------------------------------------------------------------------------------------------------------------------------------
===父类指针指向子类对象===
* 1，如果以一个父类指针指向一个子类对象，那么经由该指针只能访问基础类定义的函数(静态联翩)
* 2，如果以一个衍生类指针指向一个基础类对象，必须先做强制转型动作(explicit cast)，这种做法很危险，也不符合生活习惯，在程序设计上也会给程序员带来困扰.(一般不会这么去定义)
* 3，如果基础类和衍生类定义了相同名称的成员函数，那么通过对象指针调用成员函数时，到底调用那个函数要根据指针的原型来确定，而不是根据指针实际指向的对象类型确定。
**-----------------------------------------------------------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
* 1.product中预留了接口并由子类concreteproduct类来实现
* 2.creator中设置了关于product的接口(creator依赖于product)并由其子类concreteCreator来实现
* 3.创建concreteCreator子类来实现了concreteProduct子类中的功能
* 4.Creator的子类调用和创建了Product子类中的功能和方法，Creator的子类相当于汽车和轮船，
*   Product的子类相当于陆路运输和水路运输，创建汽车类会调用和返回陆路运输的方法，创建轮船类会
*   调用和返回水路运输的方法,同时陆路运输/水路运输可以同时包含多种交通方式
**----------------------------------------------------------------------------------------*/

/*==================================================================================================================================
===Descriptions:===
* 1.产品(Product) 将会对接口进行声明.对于所有由创建者及其子类构建的对象,这些接口都是通用的。
* 2.具体产品(Concrete Products) 是产品接口的不同实现。
* 3.创建者(Creator) 类声明返回产品对象的工厂方法。 该方法的返回对象类型必须与产品接口相匹配。
*   你可以将工厂方法声明为抽象方法， 强制要求每个子类以不同方式实现该方法。 或者， 你也可以在基础工厂方法中返回默认产品类型。
*   注意， 尽管它的名字是创建者， 但它最主要的职责并不是创建产品。 一般来说， 创建者类包含一些与产品相关的核心业务逻辑。 
*   工厂方法将这些逻辑处理从具体产品类中分离出来。 打个比方， 大型软件开发公司拥有程序员培训部门。 但是， 这些公司的主要工作还是编写代码， 而非生产程序员。
* 4.具体创建者(Concrete Creators)将会重写基础工厂方法， 使其返回不同类型的产品。
*   注意， 并不一定每次调用工厂方法都会创建新的实例。 工厂方法也可以返回缓存、 对象池或其他来源的已有对象。

===工厂方法模式适合应用场景===
  1.当你在编写代码的过程中，如果无法预知对象确切类别及其依赖关系时，可使用工厂方法。
     ~ 工厂方法将创建产品的代码与实际使用产品的代码分离， 从而能在不影响其他代码的情况下扩展产品创建部分代码。
       例如， 如果需要向应用中添加一种新产品,你只需要开发新的创建者子类，然后重写其工厂方法即可
  2.如果你希望用户能扩展你软件库或框架的内部组件，可使用工厂方法。
     ~ 继承可能是扩展软件库或框架默认行为的最简单方法。 但是当你使用子类替代标准组件时， 框架如何辨识出该子类？  
       解决方案是将各框架中构造组件的代码集中到单个工厂方法中，并在继承该组件之外允许任何人对该方法进行重写。
  3.如果你希望复用现有对象来节省系统资源， 而不是每次都重新创建对象，可使用工厂方法。
     ~ 在处理大型资源密集型对象（比如数据库连接、文件系统和网络资源）时，你会经常碰到这种资源需求。
       让我们思考复用现有对象的方法：
           a.首先,你需要创建存储空间来存放所有已经创建的对象。
           b.当他人请求一个对象时， 程序将在对象池中搜索可用对象。
           c.…然后将其返回给客户端代码。
           d.如果没有可用对象，程序则创建一个新对象（并将其添加到对象池中）。
           这些代码可不少！而且它们必须位于同一处，这样才能确保重复代码不会污染程序。可能最显而易见， 也是最方便的方式， 
           就是将这些代码放置在我们试图重用的对象类的构造函数中。但是从定义上来讲，构造函数始终返回的是新对象，其无法返回现有实例。
           因此，你需要有一个既能够创建新对象，又可以重用现有对象的普通方法。这听上去和工厂方法非常相像。

===实现方式===
  1.让所有产品都遵循同一接口。 该接口必须声明对所有产品都有意义的方法。
  2.在创建类中添加一个空的工厂方法。 该方法的返回类型必须遵循通用的产品接口。
  3.在创建者代码中找到对于产品构造函数的所有引用。 将它们依次替换为对于工厂方法的调用， 同时将创建产品的代码移入工厂方法。
    你可能需要在工厂方法中添加临时参数来控制返回的产品类型。工厂方法的代码看上去可能非常糟糕。 其中可能会有复杂的 switch分支运算符， 
    用于选择各种需要实例化的产品类。 但是不要担心， 我们很快就会修复这个问题。
  4.现在， 为工厂方法中的每种产品编写一个创建者子类， 然后在子类中重写工厂方法， 并将基本方法中的相关创建代码移动到工厂方法中。
  5.如果应用中的产品类型太多， 那么为每个产品创建子类并无太大必要， 这时你也可以在子类中复用基类中的控制参数。
  6.如果代码经过上述移动后， 基础工厂方法中已经没有任何代码， 你可以将其转变为抽象类。 如果基础工厂方法中还有其他语句， 你可以将其设置为该方法的默认行为。

===工厂方法模式优缺点===
    优点:
        你可以避免创建者和具体产品之间的紧密耦合。
        单一职责原则:你可以将产品创建代码放在程序的单一位置，从而使得代码更容易维护。
        开闭原则:无需更改现有客户端代码，你就可以在程序中引入新的产品类型。
    缺点:
        应用工厂方法模式需要引入许多新的子类， 代码可能会因此变得更复杂。 最好的情况是将该模式引入创建者类的现有层次结构中。

===与其他模式的关系===
    1.在许多设计工作的初期都会使用工厂方法模式 （较为简单， 而且可以更方便地通过子类进行定制）， 随后演化为使用抽象工厂模式、 原型模式或生成器模式 （更灵活但更加复杂）。
    2.抽象工厂模式通常基于一组工厂方法， 但你也可以使用原型模式来生成这些类的方法。
    3.你可以同时使用工厂方法和迭代器模式来让子类集合返回不同类型的迭代器， 并使得迭代器与集合相匹配。
    4.原型并不基于继承， 因此没有继承的缺点。 另一方面， 原型需要对被复制对象进行复杂的初始化。 工厂方法基于继承， 但是它不需要初始化步骤。
    5.工厂方法是模板方法模式的一种特殊形式。 同时， 工厂方法可以作为一个大型模板方法中的一个步骤。
*==================================================================================================================================*/