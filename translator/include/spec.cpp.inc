R"=====(#include "cppbdd/cppbdd.hpp"
#include "cppbdd/expect.hpp"

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
    Title("{{ title }}");
    UserStory(
##      for story in user_story
##      if loop.is_last
        "{{ story }}"
##      else
        "{{ story }}",
##      endif
##      endfor
    );
##  for scenario in scenarios
    Scenario("{{ scenario.scenario }}", [](Context& context) {
##      for given in scenario.given
##      if loop.is_first
        Given("{{ given.fmt }}",
##          if given.type == "void"
            [&](void) {
                // TODO: setup
            }
##          else
            [&]({{ given.type }} x) {
                // TODO: setup
            }, vector<{{ given.type }}> {
##              for case in given.cases
##              if given.type == "std::string"
                "{{ case }}",
##              else if given.type == "char"
                '{{ case }}',
##              else
                {{ case }},
##              endif
##              endfor
            }
##          endif
        );
##      else
        And("{{ given.fmt }}",
##          if given.type == "void"
            [&](void) {
                // TODO: setup
            }
##          else
            [&]({{ given.type }} x) {
                // TODO: setup
            }, vector<{{ given.type }}> {
##              for case in given.cases
##              if given.type == "std::string"
                "{{ case }}",
##              else if given.type == "char"
                '{{ case }}',
##              else
                {{ case }},
##              endif
##              endfor
            }
##          endif
        );
##      endif
##      endfor
##      for when in scenario.when
##      if loop.is_first
        When("{{ when.fmt }}",
##          if when.type == "void"
            [&](void) {
                // TODO: action
            }
##          else
            [&]({{ when.type }} x) {
                // TODO: action
            }, vector<{{ when.type }}> {
##              for case in when.cases
##              if when.type == "std::string"
                "{{ case }}",
##              else if when.type == "char"
                '{{ case }}',
##              else
                {{ case }},
##              endif
##              endfor
            }
##          endif
        );
##      else
        And("{{ when.fmt }}",
##          if when.type == "void"
            [&](void) {
                // TODO: action
            }
##          else
            [&]({{ when.type }} x) {
                // TODO: action
            }, vector<{{ when.type }}> {
##              for case in when.cases
##              if when.type == "std::string"
                "{{ case }}",
##              else if when.type == "char"
                '{{ case }}',
##              else
                {{ case }},
##              endif
##              endfor
            }
##          endif
        );
##      endif
##      endfor
##      for then in scenario.then
##      if loop.is_first
        Then("{{ then.fmt }}",
##          if then.type == "void"
            [&](void) {
                // TODO: assertion
            }
##          else
            [&]({{ then.type }} x) {
                // TODO: assertion
            }, vector<{{ then.type }}> {
##              for case in then.cases
##              if then.type == "std::string"
                "{{ case }}",
##              else if then.type == "char"
                '{{ case }}',
##              else
                {{ case }},
##              endif
##              endfor
            }
##          endif
        );
##      else
        And("{{ then.fmt }}",
##          if then.type == "void"
            [&](void) {
                // TODO: assertion
            }
##          else
            [&]({{ then.type }} x) {
                // TODO: assertion
            }, vector<{{ then.type }}> {
##              for case in then.cases
##              if then.type == "std::string"
                "{{ case }}",
##              else if then.type == "char"
                '{{ case }}',
##              else
                {{ case }},
##              endif
##              endfor
            }
##          endif
        );
##      endif
##      endfor
    });
##  endfor
}

int main(void) {
    init();
    cppbdd::RunTests();
    cppbdd::ShowResults();
    return 0;
})====="
