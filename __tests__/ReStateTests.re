open Jest;

describe("ReState", () => {
  open Expect;

  describe("ToggleMachine", () => {
    module ToggleMachine = {
      type state =
        | Inactive
        | Active;
      type event =
        | TOGGLE;

      let transition = (state, event) =>
        switch (state, event) {
        | (Inactive, TOGGLE) => Active
        | (Active, TOGGLE) => Inactive
        };
    };
    open ToggleMachine;

    test("state is active", () => {
      let currentState = Inactive;
      let nextState = transition(currentState, TOGGLE);

      expect(nextState) |> toBe(Active);
    });
    test("state is inactive", () => {
      let currentState = Active;
      let nextState = transition(currentState, TOGGLE);

      expect(nextState) |> toBe(Inactive);
    });
  });

  describe("ToggleMachine Polymorphic", () => {
    let transition = (state, event) =>
      switch (state, event) {
      | (`Inactive, `TOGGLE) => `Active
      | (`Active, `TOGGLE) => `Inactive
      };

    test("state is active", () => {
      let currentState = `Inactive;
      let nextState = transition(currentState, `TOGGLE);

      expect(nextState) |> toBe(`Active);
    });
    test("state is inactive", () => {
      let currentState = `Active;
      let nextState = transition(currentState, `TOGGLE);

      expect(nextState) |> toBe(`Inactive);
    });
  });

  describe("LightMachine", () => {
    module LightMachine = {
      type state =
        | Green
        | Yellow
        | Red;
      type event =
        | TIMER;

      let transition = (state, event) =>
        switch (state, event) {
        | (Green, TIMER) => Yellow
        | (Yellow, TIMER) => Red
        | (Red, TIMER) => Green
        };
    };
    open LightMachine;

    test("green to yellow", () => {
      let currentState = Green;
      let nextState = transition(currentState, TIMER);

      expect(nextState) |> toBe(Yellow);
    });

    test("yellow to red", () => {
      let currentState = Yellow;
      let nextState = transition(currentState, TIMER);

      expect(nextState) |> toBe(Red);
    });

    test("red to green", () => {
      let currentState = Red;
      let nextState = transition(currentState, TIMER);

      expect(nextState) |> toBe(Green);
    });
  });

  describe("LightMachine context, entry, actions", () => {
    module LightMachine = {
      type context = {
        redLights: int,
        yellowsTimed: int,
      };
      type state =
        | Green
        | Yellow
        | Red;
      type event =
        | TIMER;

      let transition = (~state, ~event, ~context) => {
        let previousState = state;

        let (newState, context) =
          switch (state, event) {
          | (Green, TIMER) => (Yellow, context)
          | (Yellow, TIMER) =>
            // Actions
            Js.log("Going to red!");

            // Transition action
            let context = {
              ...context,
              yellowsTimed: context.yellowsTimed + 1,
            };

            (Red, context);
          | (Red, TIMER) => (Green, context)
          };

        // Entry
        let (newState, context) =
          switch (newState) {
          | Red =>
            Js.log("Entering Red");

            let context = {...context, redLights: context.redLights + 1};

            (newState, context);
          | _ => (newState, context)
          };

        // Exit
        if (previousState !== newState) {
          switch (previousState) {
          | Red =>
            Js.log("Leaving Red");

            (newState, context);
          | _ => (newState, context)
          };
        } else {
          (newState, context);
        };
      };
    };
    open LightMachine;

    describe("green to yellow", () => {
      let currentState = Green;
      let context = {redLights: 0, yellowsTimed: 0};

      let (nextState, context) =
        transition(~state=currentState, ~event=TIMER, ~context);

      test("state", () => {
        expect(nextState) |> toBe(Yellow)
      });
      test("context", () => {
        expect(context.redLights) |> toBe(0)
      });
    });

    describe("yellow to red", () => {
      let currentState = Yellow;
      let context = {redLights: 0, yellowsTimed: 0};

      let (nextState, context) =
        transition(~state=currentState, ~event=TIMER, ~context);

      test("state", () => {
        expect(nextState) |> toBe(Red)
      });
      test("context redLights", () => {
        expect(context.redLights) |> toBe(1)
      });

      test("context yellowsTimed", () => {
        expect(context.yellowsTimed) |> toBe(1)
      });
    });

    describe("red to green", () => {
      let currentState = Red;
      let context = {redLights: 0, yellowsTimed: 0};

      let (nextState, context) =
        transition(~state=currentState, ~event=TIMER, ~context);

      test("state", () => {
        expect(nextState) |> toBe(Green)
      });
      test("context", () => {
        expect(context.redLights) |> toBe(0)
      });
    });
  });

  ();
});
