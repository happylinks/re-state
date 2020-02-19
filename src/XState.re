/*type state = Js.t({. "on": Js.t(string)});

  type machineConfig =
    Js.t({
      .
      "id": string,
      "initial": string,
      "states": Js.t(state),
    });*/

[@bs.module "@xstate/fsm"]
external createMachine: 'a => Machine.t = "createMachine";

[@bs.module "@xstate/fsm"]
external interpret: Machine.t => Service.t = "interpret";
