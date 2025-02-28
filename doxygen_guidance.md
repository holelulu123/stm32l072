# String Utilities Documentation

This file demonstrates well-written documentation using Doxygen-style tags for a C function.

## Function: `string_length`

```c
int string_length(const char *str);
/**
 * @brief Calculates the length of a null-terminated string
 * 
 * This function computes the number of characters in a string excluding
 * the null terminator ('\0').
 * 
 * @param str Pointer to a null-terminated string
 * @return int Length of the string, or -1 if str is NULL
 * 
 * @example
 *   char text[] = "Hello";
 *   int len = string_length(text);  // Returns 5
 * 
 * @note
 *   - Assumes the input string is null-terminated
 *   - Maximum length limited to INT_MAX
 * 
 * @warning
 *   - Non-null-terminated strings cause undefined behavior
 */

@brief: A short summary of what the function does.
@param [name]: Describes an input parameter (e.g., str), its type, and purpose.
@return: Explains the return value and any special cases (e.g., -1 for errors).
@example: Provides a practical code snippet showing how to use the function.
@note: Adds helpful details or assumptions about the function's behavior.
@warning: Highlights potential issues or misuse to watch out for.
