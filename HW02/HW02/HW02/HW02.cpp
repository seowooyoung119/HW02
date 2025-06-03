#include <stdio.h>
#include <iostream>
#include <cstddef>
#include <cstdlib>
#include <ctime>

/*동물 생성 클래스(부모)*/
class Animal
{
public:
    virtual void MakeSound() = 0;
    virtual ~Animal() { }
};

/*개 생성 클래스(자식)*/
class Dog : public Animal
{
public:
    void MakeSound() override { std::printf("멍멍\n"); }
    ~Dog() override { }
};

/*고양이 생성 클래스(자식)*/
class Cat : public Animal
{
public:
    void MakeSound() override { std::printf("야옹\n"); }
    ~Cat() override { }
};

/*젖소 생성 클래스(부모)*/
class Cow : public Animal
{
public:
    void MakeSound() override { std::printf("음메\n"); }
    ~Cow() override { }
};

/*동물원 생성 클래스*/
class Zoo
{
private:
    Animal* MyAnimals[10]; 

public:
    /*동물원 생성*/
    Zoo()
    {
        for (size_t i = 0; i < 10; ++i)
        {
            MyAnimals[i] = nullptr;
        }
    }

    /*동물원에 동물 입력*/
    void AddMyAnimals(Animal* animal)
    {
        if (animal == nullptr) {return;}

        for (size_t i = 0; i < 10; ++i)
        {
            if (nullptr == MyAnimals[i])
            {
                MyAnimals[i] = animal;
                return;
            }
        }

        
        std::cerr<< "동물원이 가득찼습니다.";
    }

    /*동물원의 동물 출력*/
    void performActions()
    {
        for (size_t i = 0; i < 10; ++i)
        {
            if (nullptr != MyAnimals[i])
            {
                MyAnimals[i]->MakeSound();
            }
        }
    }

    /* 동물원 소멸*/
    ~Zoo()
    {
        for (size_t i = 0; i < 10; ++i)
        {
            if (nullptr != MyAnimals[i])
            {
                delete MyAnimals[i];
                MyAnimals[i] = nullptr;
            }
        }
    }
};


/*반환 타입이 Anmal인 랜덤 동물 생성 함수*/
Animal* CreateRandomAnimal() 
{
    
    /*작동마다 랜덤 난수 생성*/
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    /*0, 1, 2 중 하나의 난수를 생성*/
    int choice = std::rand() % 3;

    /*난수 값에 따라 Dog, Cat, Cow 중 하나를 new로 동적 할당 후 반환*/
    switch (choice) {
    case 0:
        return new Dog(); 
    case 1:
        return new Cat();
    case 2:
        return new Cow();
    default:
        return nullptr;
    }
}


int main()
{
    /*동물 생성 자식, 부모 클래스 이용*/
    Animal* Animal[3];
    Animal[0] = new Dog;
    Animal[1] = new Cat;
    Animal[2] = new Cow;

    for (int i = 0; i < 3; ++i)
    {
        Animal[i]->MakeSound();
    }

    // 출력 결과:
    //멍멍
    //야옹
    //음메

    std::cout << "---------------" << std::endl;

    // 동물원 생성 
    Zoo myZoo;

    // 동물 집어넣기
    myZoo.AddMyAnimals(new Dog());
    myZoo.AddMyAnimals(new Cat());
    myZoo.AddMyAnimals(new Cow());

    // 동물원 호출
    myZoo.performActions();
    
    // 출력 결과:
    //멍멍
    //야옹
    //음메

    // 프로그램이 종료되면 myZoo의 소멸자가 자동으로 호출되어 new Dog(), new Cat(), new Cow() 메모리가 delete 됩니다.

    std::cout << "---------------" << std::endl;

    // 랜덤 동물 생성 후 반환 된 동물의 MakeSound 함수 작동 
    CreateRandomAnimal()->MakeSound();


    return 0;
}
