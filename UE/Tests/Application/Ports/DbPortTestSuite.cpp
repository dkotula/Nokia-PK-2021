#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "Mocks/ISmsDbMock.hpp"
#include "Ports/SmsDbPort.hpp"
namespace ue
{
using namespace ::testing;

class DbPortTestSuite : public Test
{
protected:
    SmsDb objectUnderTest{{Sms{PhoneNumber{1},"Message1"},Sms{PhoneNumber{2},"Message2"},Sms{PhoneNumber{3},"Message3"}}};
    DbPortTestSuite()
    {

    }
    ~DbPortTestSuite()
    {

    }
};

TEST_F(DbPortTestSuite, shallReturnCorrectSizeOfDb)
{
    EXPECT_EQ(3,objectUnderTest.size());
}

TEST_F(DbPortTestSuite, shallReturnSmsWithGivenId)
{
    EXPECT_EQ("Message1",objectUnderTest.get(0)->message);
}

TEST_F(DbPortTestSuite, shallReturnAllObject)
{
    std::vector<Sms> smsList=objectUnderTest.getAll();
    EXPECT_EQ(3,smsList.size());
    EXPECT_EQ("Message1",smsList[0].message);
    EXPECT_EQ("Message2",smsList[1].message);
    EXPECT_EQ("Message3",smsList[2].message);
}

TEST_F(DbPortTestSuite, shallInsertCorrectly)
{
    int firstSize=objectUnderTest.size();
    objectUnderTest.insert(Sms{});
    int lastSize=objectUnderTest.size();
    EXPECT_EQ(firstSize+1,lastSize);
}

TEST_F(DbPortTestSuite, shallRemoveCorrectly)
{
    int firstSize=objectUnderTest.size();
    objectUnderTest.remove(0);
    int lastSize=objectUnderTest.size();
    EXPECT_EQ(firstSize-1,lastSize);
}

TEST_F(DbPortTestSuite, shallRemoveAllCorrectly)
{
    objectUnderTest.removeAll();
    EXPECT_EQ(objectUnderTest.size(),0);
}
}