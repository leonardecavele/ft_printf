`ft_printf` is a recreation of the standard C `printf` function. It parses a format string, retrieves variadic arguments and writes the formatted result to standard output.

The function returns the number of characters written, or `-1` if a write operation fails.

### Conversions

The mandatory implementation supports `%c`, `%s`, `%p`, `%d`, `%i`, `%u`, `%x`, `%X` and `%%`.

These conversions handle characters, strings, pointers, signed and unsigned integers, and hexadecimal values.

### Bonus formatting

The bonus implementation adds the flags `-`, `0`, `#`, `+` and space, together with field width and precision.

It supports combinations such as:

```c
ft_printf("%-10s | %#08x | %+.5d\n", "value", 42, 7);
```

### Compilation

Run `make` to build the mandatory implementation as `libftprintf.a`, or `make bonus` to build the version with additional formatting options.

The targets `clean`, `fclean` and `re` are also available.

### Usage

Include the appropriate header and link the generated library:

```c
#include "ft_printf.h"

int	main(void)
{
	ft_printf("value: %d\n", 42);
	return (0);
}
```

```bash
cc main.c -I includes -L. -lftprintf -o example
./example
```

### Implementation

The format string is read one character at a time. When `%` is encountered, the corresponding argument is retrieved through `va_list` and converted to its textual representation.

The bonus parser additionally calculates prefixes, padding, precision and alignment before writing the formatted value.
