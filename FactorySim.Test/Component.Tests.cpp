#include "pch.h"

#include "Components.h"

// In product code, work ensure that repo is refactored
// into small unit testable chunks, and that all functional
// code have unit & integration test coverage.

// Here I have only tested a small subset of the component
// class structure

class TestComponentCoreFunctionality : public ::testing::Test
{
protected:
    CompBasePtr componentA;
    CompBasePtr componentB;
    CompBasePtr componentC;
    CompBasePtr componentNull;
    ComponentRandomGenerator gen;

    TestComponentCoreFunctionality() = default;

    virtual void SetUp()
    {
        componentA = std::make_unique<ComponentA>();
        componentB = std::make_unique<ComponentB>();
        componentC = std::make_unique<ComponentC>();
        componentNull = std::make_unique<ComponentNull>();
    }
};
 
TEST_F(TestComponentCoreFunctionality, General)
{
    ASSERT_EQ((size_t)ComponentHelpers::ComponentType::Count, 3);
    
    /*
    ASSERT_EQ(ComponentHelpers::Classify(this->componentA.get()), ComponentType::A);
    ASSERT_TRUE(ComponentHelpers::ClassifyToString(this->componentA.get()) == "A");

    ASSERT_EQ(ComponentHelpers::Classify(this->componentB.get()), ComponentType::B);
    ASSERT_TRUE(ComponentHelpers::ClassifyToString(this->componentB.get()) == "B");

    ASSERT_EQ(ComponentHelpers::Classify(this->componentC.get()), ComponentType::C);
    ASSERT_TRUE(ComponentHelpers::ClassifyToString(this->componentC.get()) == "C");

    ASSERT_EQ(ComponentHelpers::Classify(this->componentNull.get()), ComponentType::Null);
    ASSERT_TRUE(ComponentHelpers::ClassifyToString(this->componentNull.get()) == "Null");
    */
}

TEST_F(TestComponentCoreFunctionality, ComponentA)
{
    ASSERT_FALSE(this->componentA->IsNull());
    ASSERT_FALSE(this->componentA->IsProduct());
    ASSERT_GE(this->componentA->SpawnProbability(), 0.0);
    ASSERT_TRUE(this->componentA->ToString() == "A");
}

TEST_F(TestComponentCoreFunctionality, ComponentB)
{
    ASSERT_FALSE(this->componentB->IsNull());
    ASSERT_FALSE(this->componentB->IsProduct());
    ASSERT_GE(this->componentB->SpawnProbability(), 0.0);
    ASSERT_TRUE(this->componentB->ToString() == "B");
}

TEST_F(TestComponentCoreFunctionality, ComponentC)
{
    ASSERT_FALSE(this->componentC->IsNull());
    ASSERT_FALSE(this->componentC->IsProduct());
    ASSERT_GE(this->componentC->SpawnProbability(), 0.0);
    ASSERT_TRUE(this->componentC->ToString() == "C");
}

TEST_F(TestComponentCoreFunctionality, ComponentNull)
{
    ASSERT_TRUE(this->componentNull->IsNull());
    ASSERT_FALSE(this->componentNull->IsProduct());
    ASSERT_GE(this->componentNull->SpawnProbability(), 0.0);
    ASSERT_TRUE(this->componentNull->ToString() == "");
}

TEST_F(TestComponentCoreFunctionality, ComponentGenerationProbability)
{
    const size_t trails = 1'000'000;
    std::unordered_map<ComponentType, size_t> generator_count;

    for (size_t idx = 0; idx < trails; ++idx)
    {
        auto comp = gen.Generate();
        
        if (comp)
        {
            generator_count[ComponentHelpers::Classify(comp.get())]++;
        }
    }

    EXPECT_NEAR((double)generator_count[ComponentType::A] / (double)trails, this->componentA->SpawnProbability(), 0.05);
    EXPECT_NEAR((double)generator_count[ComponentType::B] / (double)trails, this->componentB->SpawnProbability(), 0.05);
    EXPECT_NEAR((double)generator_count[ComponentType::C] / (double)trails, this->componentC->SpawnProbability(), 0.05);
}

TEST_F(TestComponentCoreFunctionality, ComponentComparisons)
{
    auto currentComponentA = dynamic_cast<ComponentA*>(this->componentA.get());
    auto currentComponentB = dynamic_cast<ComponentB*>(this->componentB.get());
    auto currentComponentC = dynamic_cast<ComponentC*>(this->componentC.get());
    auto currentComponentNull = dynamic_cast<ComponentNull*>(this->componentNull.get());

    auto newComponentA = std::make_unique<ComponentA>();

    ASSERT_EQ(*newComponentA, *currentComponentA);
    ASSERT_NE(*currentComponentA, *currentComponentB);
    ASSERT_NE(*currentComponentA, *currentComponentC);
    ASSERT_NE(*currentComponentA, *currentComponentNull);
}