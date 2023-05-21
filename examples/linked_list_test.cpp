#include "cppbdd/cppbdd.hpp"
#include <functional>
#include <vector>
#include <tuple>
#include <cassert>

#include <list>

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

    Scenario("Inserting new element at the end of the list should increase the length of the list", [](void) {
        cppbdd::TaskManager stmt_manager;
        list<int> l;

        Given("an int linked list with length {}", [&](int x) {
                l.clear();
                while (x--) l.push_back(0);
            },
            vector<tuple<int>> {
                tuple<int>(1),
                tuple<int>(0)
            },
            stmt_manager);

        When("inserting {} at the end of the list", [&](int x) {
                l.push_back(x);
            },
            vector<tuple<int>> {
               tuple<int>(5),
               tuple<int>(-1)
            },
            stmt_manager);

        Then("the length of it should be {}", [&](int x) {
                int len = 0;
                for (auto it = l.begin(); it != l.end(); it++, len++);
                assert(len == x);
            },
            vector<tuple<int>> {
               tuple<int>(2),
               tuple<int>(1)
            },
            stmt_manager);

        And("the last element of it should be {}", [&](int x) {
                assert(*l.rbegin() == x);
            },
            vector<tuple<int>> {
                tuple<int>(5),
                tuple<int>(-1)
            },
            stmt_manager);

        stmt_manager.runAll();
    });

    Scenario("Attempting to pop elements from a linked list should decrease its length", [](void) {
        cppbdd::TaskManager stmt_manager;
        list<int> l;

        Given("an int linked list with legnth {}", [&](int x) {
                l.clear();
                while (x--) l.push_back(0);
            },
            vector<tuple<int>> {
                tuple<int>(1)
            },
            stmt_manager);

        When("attempting to pop the last element of the list", [&](void) {
                l.pop_back();
            },
            stmt_manager);

        Then("the length of it should be {}", [&](int x) {
                int len = 0;
                for (auto it = l.begin(); it != l.end(); it++, len++);
                assert(len == x);
            },
            vector<tuple<int>> {
                tuple<int>(0)
            },
            stmt_manager);

        stmt_manager.runAll();
    });
}

int main(void) {
    init();
    cppbdd::runTests();
    return 0;
}
