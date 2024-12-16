// Uncomment the next line to use precompiled headers
#include "pch.h"
// uncomment the next line if you do not use precompiled headers
//#include "gtest/gtest.h"
//
// the global test environment setup and tear down
// you should not need to change anything here
class Environment : public ::testing::Environment
{
public:
    ~Environment() override {}

    // Override this to define how to set up the environment.
    void SetUp() override
    {
        // initialize random seed for generating random values
        srand(time(nullptr));
    }

    // Override this to define how to tear down the environment.
    void TearDown() override {}
};

// create our test class to house shared data between tests
// you should not need to change anything here
class CollectionTest : public ::testing::Test
{
protected:
    // create a smart pointer to hold our collection
    std::unique_ptr<std::vector<int>> collection;

    void SetUp() override
    {
        // create a new collection to be used in the test
        collection.reset(new std::vector<int>);
    }

    void TearDown() override
    {
        // check if collection is not null before clearing and resetting
        if (collection)
        {
            // erase all elements in the collection, if any remain
            collection->clear();
            // free the pointer
            collection.reset(nullptr);
        }
    }
    // helper function to add random values from 0 to 99 count times to the collection
    void add_entries(int count)
    {
        assert(count > 0);
        for (auto i = 0; i < count; ++i)
            collection->push_back(rand() % 100);
    }
};

// When should you use the EXPECT_xxx or ASSERT_xxx macros?
// Use ASSERT when failure should terminate processing, such as the reason for the test case.
// Use EXPECT when failure should notify, but processing should continue

// Test that a collection is empty when created.
// Prior to calling this (and all other TEST_F defined methods),
// CollectionTest::StartUp is called.
// Following this method (and all other TEST_F defined methods),
// CollectionTest::TearDown is called
TEST_F(CollectionTest, CollectionSmartPointerIsNotNull)
{
    // is the collection created
    ASSERT_TRUE(collection);

    // if empty, the size must be 0
    ASSERT_NE(collection.get(), nullptr);
}

// Test that a collection is empty when created.
TEST_F(CollectionTest, IsEmptyOnCreate)
{
    // is the collection empty?
    ASSERT_TRUE(collection->empty());

    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);
}

/* Comment this test out to prevent the test from running
 * Uncomment this test to see a failure in the test explorer */
TEST_F(CollectionTest, AlwaysFail)
{
    FAIL();
}

// TODO: Create a test to verify adding a single value to an empty collection
TEST_F(CollectionTest, CanAddToEmptyVector)
{
    // is the collection empty?
    ASSERT_TRUE(collection->empty());
    ASSERT_EQ(collection->size(), 0);

    // add one entry to the collection
    add_entries(1);

    // verify the collection is not empty and has size 1
    ASSERT_FALSE(collection->empty());
    EXPECT_EQ(collection->size(), 1);
}

// TODO: Create a test to verify adding five values to collection
TEST_F(CollectionTest, CanAddFiveValuesToVector)
{
    // add five entries to the collection
    add_entries(5);

    // verify the collection size is 5
    ASSERT_FALSE(collection->empty());
    EXPECT_EQ(collection->size(), 5);
}

// TODO: Create a test to verify that max size is greater than or equal to size for 0, 1, 5, 10 entries
TEST_F(CollectionTest, MaxSizeIsGreaterThanOrEqualToSize)
{
    // check max size for various entry counts
    EXPECT_GE(collection->max_size(), collection->size());
    add_entries(1);
    EXPECT_GE(collection->max_size(), collection->size());
    add_entries(4);
    EXPECT_GE(collection->max_size(), collection->size());
    add_entries(5);
    EXPECT_GE(collection->max_size(), collection->size());
}

// TODO: Create a test to verify that capacity is greater than or equal to size for 0, 1, 5, 10 entries
TEST_F(CollectionTest, CapacityIsGreaterThanOrEqualToSize)
{
    // check capacity for various entry counts
    EXPECT_GE(collection->capacity(), collection->size());
    add_entries(1);
    EXPECT_GE(collection->capacity(), collection->size());
    add_entries(4);
    EXPECT_GE(collection->capacity(), collection->size());
    add_entries(5);
    EXPECT_GE(collection->capacity(), collection->size());
}

// TODO: Create a test to verify resizing increases the collection
TEST_F(CollectionTest, ResizeIncreasesCollection)
{
    // resize the collection to 10 and verify size
    collection->resize(10);
    EXPECT_EQ(collection->size(), 10);
}

// TODO: Create a test to verify resizing decreases the collection
TEST_F(CollectionTest, ResizeDecreasesCollection)
{
    // add entries and resize to smaller size
    add_entries(10);
    collection->resize(5);
    EXPECT_EQ(collection->size(), 5);
}

// TODO: Create a test to verify resizing decreases the collection to zero
TEST_F(CollectionTest, ResizeToZero)
{
    // add entries and resize to zero
    add_entries(10);
    collection->resize(0);
    EXPECT_EQ(collection->size(), 0);
    EXPECT_TRUE(collection->empty());
}

// TODO: Create a test to verify clear erases the collection
TEST_F(CollectionTest, ClearErasesCollection)
{
    // add entries and clear the collection
    add_entries(10);
    collection->clear();
    EXPECT_EQ(collection->size(), 0);
    EXPECT_TRUE(collection->empty());
}

// TODO: Create a test to verify erase(begin,end) erases the collection
TEST_F(CollectionTest, EraseBeginEndErasesCollection)
{
    // add entries and erase all using begin and end
    add_entries(10);
    collection->erase(collection->begin(), collection->end());
    EXPECT_EQ(collection->size(), 0);
    EXPECT_TRUE(collection->empty());
}

// TODO: Create a test to verify reserve increases the capacity but not the size of the collection
TEST_F(CollectionTest, ReserveIncreasesCapacityNotSize)
{
    // reserve capacity and check size and capacity
    size_t initial_capacity = collection->capacity();
    collection->reserve(20);
    EXPECT_GT(collection->capacity(), initial_capacity);
    EXPECT_EQ(collection->size(), 0);
}

// TODO: Create a test to verify the std::out_of_range exception is thrown when calling at() with an index out of bounds
// NOTE: This is a negative test
TEST_F(CollectionTest, OutOfRangeThrowsException)
{
    // add entries and access an out-of-bounds index
    add_entries(5);
    EXPECT_THROW(collection->at(10), std::out_of_range);
}

// TODO: Create 2 unit tests of your own to test something on the collection - do 1 positive & 1 negative

// positive test: verify adding duplicates to the collection
TEST_F(CollectionTest, CanAddDuplicates)
{
    // add entries including duplicates and verify counts
    add_entries(5);
    collection->push_back(10);
    collection->push_back(10);
    EXPECT_EQ(std::count(collection->begin(), collection->end(), 10), 2);
}

// negative test: verify accessing a null pointer throws an exception
TEST_F(CollectionTest, AccessingNullCollectionThrows)
{
    // reset the collection to null
    collection.reset();

    // check that accessing a null collection throws an exception
    EXPECT_THROW({
        if (!collection) throw std::runtime_error("Collection is null");
        collection->at(0);
        }, std::runtime_error);
}
