type t;
type state = {value: string};

[@bs.send] external send: (t, string) => unit = "send";
[@bs.send] external start: t => unit = "start";
[@bs.send] external stop: t => unit = "stop";
[@bs.send] external subscribe: (t, state => unit) => unit = "subscribe";
[@bs.get] external getValue: t => string = "value";
