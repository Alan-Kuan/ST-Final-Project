#include "cppbdd/cppbdd.hpp"
#include "cppbdd/expect.hpp"
#include <functional>
#include <vector>

#include <list>

typedef cppbdd::ScenarioTask::Context Context;

using cppbdd::Title;
using cppbdd::UserStory;
using cppbdd::Scenario;
using cppbdd::Given;
using cppbdd::When;
using cppbdd::Then;
using cppbdd::And;

using namespace std;

void init(void) {
    Title("Basic methods of a linked list");
    UserStory("As a library user,",
              "I want to insert and pop elements from the linked list properly,",
              "so that I can ensure the quality of my program.");

    Scenario("Inserting new element at the end of the list should increase the length of the list",
             [](Context& context) {

        Given("an int linked list with length {}", [&](int x) {
                list<int> l;
                while (x--) l.push_back(0);
                context["list"] = l;
            },
            vector<int> {1, 0});

        When("inserting {} at the end of the list", [&](int x) {
                auto& l = any_cast<list<int>&>(context["list"]);
                l.push_back(x);
            },
            vector<int> {5, -1});

        Then("the length of it should be {}", [&](int x) {
                auto& l = any_cast<list<int>&>(context["list"]);
                int len = 0;
                for (auto it = l.begin(); it != l.end(); it++, len++);
                cppbdd::expect_eq(len, x);
            },
            vector<int> {2, 1});

        And("the last element of it should be {}", [&](int x) {
                auto& l = any_cast<list<int>&>(context["list"]);
                cppbdd::expect_eq(*l.rbegin(), x);
            },
            vector<int> {5, -1});
    });

    Scenario("Attempting to pop elements from a linked list should decrease its length",
             [](Context& context) {

        Given("an int linked list with legnth {}", [&](int x) {
                list<int> l;
                while (x--) l.push_back(0);
                context["list"] = l;
            },
            vector<int> {1});

        When("attempting to pop the last element of the list", [&](void) {
                auto& l = any_cast<list<int>&>(context["list"]);
                l.pop_back();
            });

        Then("the length of it should be {}", [&](int x) {
                auto& l = any_cast<list<int>&>(context["list"]);
                int len = 0;
                for (auto it = l.begin(); it != l.end(); it++, len++);
                cppbdd::expect_eq(len, x);
            },
            vector<int> {0});
    });
}

int main(void) {
    init();
    cppbdd::runTests();
    cppbdd::showResults();
    return 0;
}
