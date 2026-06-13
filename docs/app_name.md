# app_name header

The `app_name` header refers to the `AppName` struct and its helper implements (functions):

## Structs

`app_name` header owns the `AppName` struct definition only.

### AppName

```c
typedef struct {
  enum { FROM_STDIN, CUSTOM } kind;
  union {
    StdinArgs *args;
    char custom[APP_NAME_MAX_LENGTH];
  };
} AppName;
```

The `AppName` struct holds a `kind` which specifies the current naming state:
- `FROM_STDIN`:
  > take the name passed through `stdin` (same as `argv[0]`).
- `CUSTOM`:
  > the name was specified by the user, use it!

Even when `AppName.kind` refers to a single state, the `AppName` holds both `StdinArgs *`[^StdinArgs] and
`char custom[_]`. This helps to prevent user access at invalid mem (just use the
[`app_name_get_name`](#app_name_get_name) function).

> [!IMPORTANT]
>
> Note that the `AppName.custom` field is a char array that can only contains
> [`APP_NAME_MAX_LENGTH`](#app_name_max_length) elements and it shouldn't be set manually. Use the
> [`app_name_set_custom_name`](#app_name_set_custom_name) instead!

## Functions

[`AppName`](#appname) related functions.

### app_name_new

```c
AppName app_name_new(StdinArgs *args) { /* ... */ }
```

Creates a new `AppName` from the given `StdinArgs`[^StdinArgs] pointer.

The `AppName` is `FROM_STIN` kind by default and gonna point to `StdinArgs *args` (even the pointer
is `NULL`, read [`APP_NAME_NULL_PLACEHOLDER`](#app_name_null_placeholder)).

Consider using the [`app_name_set_custom_name`](#app_name_set_custom_name) function to set a new
name.

### app_name_set_custom_name

```c
AppName *app_name_set_custom_name(AppName *self, char *name) { /* ... */ }
```

Set a new name to the self `AppName *` and returns the self pointer.

If:
- `self` is `NULL`: nothing is done and `NULL` is returned
- `name` is `NULL`: nothing is done and `self` is returned (not changed)
- `strncpy_s` function fails (when `name` length is greater than
  [`APP_NAME_MAX_LENGTH`](#app_name_max_length) or something): `self->kind` still points to
  previous state + `self` is returned
- othercase (success): changes are done and self is returned

### app_name_set_from_stdin

```c
AppName *app_name_set_from_stdin(AppName *self, StdinArgs *args);
```

Set the `StdinArgs`[^StdinArgs] pointer ar inner naming and returns the `self` pointer.
fail updating if any of pointers is `NULL`.

### app_name_get_name

```c
char *app_name_get_name(AppName *self);
```

Returns the `char *` of the self `AppName`.
[`APP_NAME_NULL_PLACEHOLDER`](#app_name_null_placeholder) is returned if fails at pointer catching
(`self` or it's required inner fields = `NULL`).

## Defines

### APP_NAME_MAX_LENGTH

```c
#define APP_NAME_MAX_LENGTH 64
```

Defines the max size of a `custom` kind app name (not required for `StdinArgs *` since it isn't a
buffer, just points to data instead).

This value is currently set to `64`, which means that the custom app name can be `63` chars long +
`\\0` (null terminator).

### APP_NAME_NULL_PLACEHOLDER

```c
#define APP_NAME_NULL_PLACEHOLDER "<NULL POINTER BEING USED>"
```

Default `char *` when `AppName` inner fields leads user to a `NULL POINTER` (better than crashing,
I guess).

### PATH_SEPARATOR

```c
#if defined(_WIN32) || defined(_WIN64)
#define PATH_SEPARATOR "\\"
#else
#define PATH_SEPARATOR "/"
#endif
```

Means the path separator according to the platform OS. this


[^StdinArgs]: Struct that holds the `argc` and `argv` values. Mentioned at
  [stdin_args.md](stdin_args.md).
