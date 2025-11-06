#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../include/Awards.h"

class RankListStub : public awards::RankList {
public:
    explicit RankListStub(const std::vector<std::string>& names) : names(names), index(0) {}

    std::string getNext() override {
        if (index < names.size()) {
            return names[index++];
        }
        return ""; // or handle this case accordingly
    }

private:
    const std::vector<std::string>& names;
    int index;
};

class AwardCeremonyActionsMock : public awards::AwardCeremonyActions {
    public:
    MOCK_METHOD(void, playAnthem, (), (override));
    MOCK_METHOD(void, turnOffTheLightsAndGoHome, (), (override));
    MOCK_METHOD(void, awardBronze, (std::string recipient), (override));
    MOCK_METHOD(void, awardSilver, (std::string recipient), (override));
    MOCK_METHOD(void, awardGold, (std::string recipient), (override));
};

TEST(AwardsTests, PerformAwardCeremony) {
    std::vector<std::string> names = {"Alice", "Bob", "Charlie"};
    RankListStub rankListStub(names);
    AwardCeremonyActionsMock actionsMock;

    // Set up expectations for the mock methods
    EXPECT_CALL(actionsMock, playAnthem()).Times(1);
    EXPECT_CALL(actionsMock, awardBronze("Alice")).Times(1);
    EXPECT_CALL(actionsMock, awardSilver("Bob")).Times(1);
    EXPECT_CALL(actionsMock, awardGold("Charlie")).Times(1);
    EXPECT_CALL(actionsMock, turnOffTheLightsAndGoHome()).Times(1);

    // Call the function under test
    awards::performAwardCeremony(rankListStub, actionsMock);
}
