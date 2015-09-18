namespace py light 

struct AddArgs {
  1: required string key,
  2: required string value,
  3: optional i64 ttl = 15,
}

exception InvalidArgsException {
  1: i64 errorCode,
  2: string message,
}

service LightService {

  void ping(),

  void add(
	1: AddArgs addArgs,
  ) throws (
	1: InvalidArgsException e,
  ),

  string get(
	1: string key,
  ),
}
