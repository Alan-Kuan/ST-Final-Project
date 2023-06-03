#include "cppbdd/cppbdd.hpp"
#include "cppbdd/expect.hpp"

typedef cppbdd::ScenarioTask::Context Context;

using cppbdd::Title;
using cppbdd::UserStory;
using cppbdd::Scenario;
using cppbdd::Given;
using cppbdd::When;
using cppbdd::Then;
using cppbdd::And;

void init() {
    Title("All-failed test");
    UserStory("As a framework developer,",
              "I want to show you an example of failed expectations,",
              "so I wrote this test file.");

    Scenario("All tests will fail", [](Context) {
        Given("nothing", []() {});
        When("nothing happened", []() {});
        Then("expect true", []() {
            cppbdd::ExpectTrue(false);
        });
        And("expect false", []() {
            cppbdd::ExpectFalse(true);
        });
        And("expect equal", []() {
            cppbdd::ExpectEqual(0, 1);
        });
        And("expect not equal", []() {
            cppbdd::ExpectNotEqual(0, 0);
        });
        And("expect less than", []() {
            cppbdd::ExpectLessThan(1, 0);
        });
        And("expect less than or equal", []() {
            cppbdd::ExpectLessThanOrEqual(1, 0);
        });
        And("expect greater than", []() {
            cppbdd::ExpectGreaterThan(0, 1);
        });
        And("expect greater than or equal", []() {
            cppbdd::ExpectGreaterThanOrEqual(0, 1);
        });
    });
}

int main(void) {
    init();
    cppbdd::RunTests();
    cppbdd::ShowResults();
    return 0;
}
