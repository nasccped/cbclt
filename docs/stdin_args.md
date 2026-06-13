# stdin_args header

The `stdin_args` header refers to the `StdinArgs` struct and its helper implements (functions):

## Structs

`stdin_args` header owns the `StdinArgs` struct definition only.

## StdinArgs

```c
typedef struct {
  int count;
  char **args;
} StdinArgs;
```

The `StdinArgs` holds the `int count` and the `char **args` (equivalent to `int main(int, char **)`
function - not automatically, it must be set or built with [`stdin_args_new`](#stdin_args_new)
function).

## Functions

[`StdinArgs`](#stdinargs) related functions.

### stdin_args_new

```c
StdinArgs stdin_args_new(int argc, char **argv) { /* ... */ }
```

Creates a new [`StdinArgs`](#stdinargs) over an an `arg count` and `arg values` (from `main`
function).

### stdin_args_get_n

```c
char *stdin_args_get_n(StdinArgs *self, size_t n) { /* ... */ }
```

Get the `n`° `char *` from the self `StdinArgs` pointer.

Returns `NULL` if:
- `self` is `NULL`
- `n` is less than `0`
- `n` is equals or greater than `self->argc`
