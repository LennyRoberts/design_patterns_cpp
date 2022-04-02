#ifndef ABSTRACT_FACTORY_H
#define ABSTRACT_FACTORY_H

#include <iostream>

using namespace std;

/**
 * Each distinct product of a product family should have a base interface. All
 * variants of the product must implement this interface.
 */
class AbstractProductA
{
public:
    virtual ~AbstractProductA(){};
    virtual std::string UsefulFunctionA() const = 0;
};

/**
 * Concrete Products are created by corresponding Concrete Factories.
 */
class ConcreteProductA1 : public AbstractProductA
{
public:
    std::string UsefulFunctionA() const override{
        return "The result of the product A1.";
    }
};

class ConcreteProductA2 : public AbstractProductA
{
    std::string UsefulFunctionA() const override{
        return "The result of the product A2.";
    }
};

/**
 * Here's the the base interface of another product. All products can interact
 * with each other, but proper interaction is possible only between products of
 * the same concrete variant.
 */
class AbstractProductB
{
    /**
     * Product B is able to do its own thing...
     */
public:
    virtual ~AbstractProductB(){};
    virtual std::string UsefulFunctionB() const = 0;
    /**
     * ...but it also can collaborate with the ProductA.
     *
     * The Abstract Factory makes sure that all products it creates are of the
     * same variant and thus, compatible.
     */
    virtual std::string AnotherUsefulFunctionB(const AbstractProductA &collaborator) const = 0;
};

/**
 * Concrete Products are created by corresponding Concrete Factories.
 */
class ConcreteProductB1 : public AbstractProductB
{
public:
    std::string UsefulFunctionB() const override{
        return "The result of the product B1.";
    }
    /**
     * The variant, Product B1, is only able to work correctly with the variant,
     * Product A1. Nevertheless, it accepts any instance of AbstractProductA as an
     * argument.
     */
    std::string AnotherUsefulFunctionB(const AbstractProductA &collaborator) const override{
        const std::string result = collaborator.UsefulFunctionA();
        return "The result of the B1 collaborating with ( " + result + " )";
    }
};

class ConcreteProductB2 : public AbstractProductB
{
public:
    std::string UsefulFunctionB() const override{
        return "The result of the product B2.";
    }
    /**
     * The variant, Product B2, is only able to work correctly with the variant,
     * Product A2. Nevertheless, it accepts any instance of AbstractProductA as an
     * argument.
     */
    std::string AnotherUsefulFunctionB(const AbstractProductA &collaborator) const override{
        const std::string result = collaborator.UsefulFunctionA();
        return "The result of the B2 collaborating with ( " + result + " )";
    }
};

/**
 * The Abstract Factory interface declares a set of methods that return
 * different abstract products. These products are called a family and are
 * related by a high-level theme or concept. Products of one family are usually
 * able to collaborate among themselves. A family of products may have several
 * variants, but the products of one variant are incompatible with products of
 * another.
 */
class AbstractFactory
{
public:
    virtual AbstractProductA *CreateProductA() const = 0;
    virtual AbstractProductB *CreateProductB() const = 0;
};

/**
 * Concrete Factories produce a family of products that belong to a single
 * variant. The factory guarantees that resulting products are compatible. Note
 * that signatures of the Concrete Factory's methods return an abstract product,
 * while inside the method a concrete product is instantiated.
 */
class ConcreteFactory1 : public AbstractFactory
{
public:
    AbstractProductA *CreateProductA() const override{
        return new ConcreteProductA1();
    }

    AbstractProductB *CreateProductB() const override{
        return new ConcreteProductB1();
    }
};

/**
 * Each Concrete Factory has a corresponding product variant.
 */
class ConcreteFactory2 : public AbstractFactory
{
public:
    AbstractProductA *CreateProductA() const override{
        return new ConcreteProductA2();
    }

    AbstractProductB *CreateProductB() const override{
        return new ConcreteProductB2();
    }
};

/**
 * The client code works with factories and products only through abstract
 * types: AbstractFactory and AbstractProduct. This lets you pass any factory or
 * product subclass to the client code without breaking it.
 */
void ClientCode(const AbstractFactory &factory)
{
    const AbstractProductA *product_a = factory.CreateProductA();
    const AbstractProductB *product_b = factory.CreateProductB();
    std::cout << product_b->UsefulFunctionB() << "\n";
    std::cout << product_b->AnotherUsefulFunctionB(*product_a) << "\n";
    delete product_a;
    delete product_b;
}

int MainAbstractFactory()
{
    std::cout << "Client: Testing client code with the first factory type:\n";
    ConcreteFactory1 *f1 = new ConcreteFactory1();
    ClientCode(*f1);
    delete f1;
    std::cout << std::endl;
    std::cout << "Client: Testing the same client code with the second factory type:\n";
    ConcreteFactory2 *f2 = new ConcreteFactory2();
    ClientCode(*f2);
    delete f2;
    return 0;
}

#endif  //!ABSTRACT_FACTORY_H

/*==========================================================================================================================
* 首先， 抽象工厂模式建议为系列中的每件产品明确声明接口,然后,确保所有产品变体都继承这些接口。
*
* ===Description:===
* 1.抽象产品（Abstract Product） 为构成系列产品的一组不同但相关的产品声明接口。
* 2.具体产品（Concrete Product） 是抽象产品的多种不同类型实现。 所有变体 （维多利亚/现代） 都必须实现相应的抽象产品 （椅子/沙发）。
* 3.抽象工厂（Abstract Factory） 接口声明了一组创建各种抽象产品的方法。
* 4.具体工厂（Concrete Factory） 实现抽象工厂的构建方法。 每个具体工厂都对应特定产品变体， 且仅创建此种产品变体。
* 5.尽管具体工厂会对具体产品进行初始化， 其构建方法签名必须返回相应的抽象产品。 这样， 使用工厂类的客户端代码就不会与工厂创建的特定产品变体耦合。 
*   客户端（Client）只需通过抽象接口调用工厂和产品对象， 就能与任何具体工厂/产品变体交互。
*
* ===抽象工厂模式适合应用场景===
* 1.如果代码需要与多个不同系列的相关产品交互，但是由于无法提前获取相关信息，或者出于对未来扩展性的考虑，你不希望代码基于产品的具体类进行构建，在这种情况下，你可以使用抽象工厂。
*   ~ 抽象工厂为你提供了一个接口，可用于创建每个系列产品的对象。只要代码通过该接口创建对象，那么你就不会生成与应用程序已生成的产品类型不一致的产品。
* 2.如果你有一个基于一组抽象方法的类，且其主要功能因此变得不明确，那么在这种情况下可以考虑使用抽象工厂模式。
*   ~ 在设计良好的程序中，每个类仅负责一件事。如果一个类与多种类型产品交互，就可以考虑将工厂方法抽取到独立的工厂类或具备完整功能的抽象工厂类中。
*
* ===实现方式===
* 1.以不同的产品类型与产品变体为维度绘制矩阵。
* 2.为所有产品声明抽象产品接口。 然后让所有具体产品类实现这些接口。
* 3.声明抽象工厂接口， 并且在接口中为所有抽象产品提供一组构建方法。
* 4.为每种产品变体实现一个具体工厂类。
* 5.在应用程序中开发初始化代码。 该代码根据应用程序配置或当前环境， 对特定具体工厂类进行初始化。 然后将该工厂对象传递给所有需要创建产品的类。
* 6.找出代码中所有对产品构造函数的直接调用， 将其替换为对工厂对象中相应构建方法的调用。
* 

* ===抽象工厂模式优缺点===
* 优点:
*     1.你可以确保同一工厂生成的产品相互匹配。
*     2.你可以避免客户端和具体产品代码的耦合。
*     3.单一职责原则。 你可以将产品生成代码抽取到同一位置， 使得代码易于维护。
*     4.开闭原则。 向应用程序中引入新产品变体时， 你无需修改客户端代码。
* 缺点:
*     1.由于采用该模式需要向应用中引入众多接口和类， 代码可能会比之前更加复杂。
*
* ===与其他模式的关系===
* ~ 在许多设计工作的初期都会使用工厂方法模式(较为简单， 而且可以更方便地通过子类进行定制),随后演化为使用抽象工厂模式、 原型模式或生成器模式（更灵活但更加复杂）。
* ~ 生成器重点关注如何分步生成复杂对象。 抽象工厂专门用于生产一系列相关对象。 抽象工厂会马上返回产品， 生成器则允许你在获取产品前执行一些额外构造步骤。
* ~ 抽象工厂模式通常基于一组工厂方法， 但你也可以使用原型模式来生成这些类的方法。
* ~ 当只需对客户端代码隐藏子系统创建对象的方式时， 你可以使用抽象工厂来代替外观模式。
* ~ 你可以将抽象工厂和桥接模式搭配使用。 如果由桥接定义的抽象只能与特定实现合作， 这一模式搭配就非常有用。 在这种情况下， 抽象工厂可以对这些关系进行封装， 并且对客户端代码隐藏其复杂性。
* ~ 抽象工厂、 生成器和原型都可以用单例模式来实现。
**==========================================================================================================================*/