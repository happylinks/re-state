type t;

[@bs.send] external transition: (t, string, string) => t = "transition";
[@bs.get] external getValue: t => string = "value";
