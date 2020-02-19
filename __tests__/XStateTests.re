open Jest;

describe("XState", () => {
  open XState;
  open Expect;

  describe("ToggleMachine (machine)", () => {
    let toggleMachine =
      createMachine({
        "id": "toggle",
        "initial": "inactive",
        "states": {
          "inactive": {
            "on": {
              "TOGGLE": "active",
            },
          },
          "active": {
            "on": {
              "TOGGLE": "inactive",
            },
          },
        },
      });

    test("state is active", () => {
      let currentState = "inactive";
      let nextState =
        toggleMachine
        ->Machine.transition(currentState, "TOGGLE")
        ->Machine.getValue;

      expect(nextState) |> toBe("active");
    });

    test("state is inactive", () => {
      let currentState = "active";
      let nextState =
        toggleMachine
        ->Machine.transition(currentState, "TOGGLE")
        ->Machine.getValue;

      expect(nextState) |> toBe("inactive");
    });
  });

  describe("ToggleMachine (service)", () => {
    let toggleMachine =
      createMachine({
        "id": "toggle",
        "initial": "inactive",
        "states": {
          "inactive": {
            "on": {
              "TOGGLE": "active",
            },
          },
          "active": {
            "on": {
              "TOGGLE": "inactive",
            },
          },
        },
      });

    let service = interpret(toggleMachine);
    service->Service.start;
    /* test("state is active", () => {
         let subscription = service->Service.subscribe(state => {Js.log(state)});
         service->Service.send("TOGGLE");

         expect(service->Service.getValue) |> toBe("active");
       });

       test("state is inactive", () => {
         service->Service.send("TOGGLE");

         expect(service->Service.getValue) |> toBe("inactive");
       });*/
  });

  describe("LightMachine", () => {
    let lightMachine =
      createMachine({
        "id": "light",
        "initial": "green",
        "states": {
          "green": {
            "on": {
              "TIMER": "yellow",
            },
          },
          "yellow": {
            "on": {
              "TIMER": "red",
            },
          },
          "red": {
            "on": {
              "TIMER": "green",
            },
          },
        },
      });

    test("green to yellow", () => {
      let currentState = "green";
      let nextState =
        lightMachine
        ->Machine.transition(currentState, "TIMER")
        ->Machine.getValue;

      expect(nextState) |> toBe("yellow");
    });

    test("yellow to red", () => {
      let currentState = "yellow";
      let nextState =
        lightMachine
        ->Machine.transition(currentState, "TIMER")
        ->Machine.getValue;

      expect(nextState) |> toBe("red");
    });

    test("red to green", () => {
      let currentState = "red";
      let nextState =
        lightMachine
        ->Machine.transition(currentState, "TIMER")
        ->Machine.getValue;

      expect(nextState) |> toBe("green");
    });
  });

  ();
});
