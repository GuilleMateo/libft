#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include "libft.h"

// https://opensource.apple.com/source/Libc/Libc-825.25/string/strlcat.c.auto.html
size_t strlcat(char * dst, const char * src, size_t maxlen) {
    const size_t srclen = strlen(src);
    const size_t dstlen = strnlen(dst, maxlen);
    if (dstlen == maxlen) return maxlen+srclen;
    if (srclen < maxlen-dstlen) {
        memcpy(dst+dstlen, src, srclen+1);
    } else {
        memcpy(dst+dstlen, src, maxlen-1);
        dst[dstlen+maxlen-1] = '\0';
    }
    return dstlen + srclen;
}

// https://opensource.apple.com/source/Libc/Libc-825.25/string/strlcpy.c.auto.html
size_t strlcpy(char * dst, const char * src, size_t maxlen) {
    const size_t srclen = strlen(src);
    if (srclen < maxlen) {
        memcpy(dst, src, srclen+1);
    } else if (maxlen != 0) {
        memcpy(dst, src, maxlen-1);
        dst[maxlen-1] = '\0';
    }
    return srclen;
}

// https://github.com/lattera/freebsd/blob/master/lib/libc/string/strnstr.c
char *strnstr(const char *s, const char *find, size_t slen) {
	char c, sc;
	size_t len;

	if ((c = *find++) != '\0') {
		len = strlen(find);
		do {
			do {
				if (slen-- < 1 || (sc = *s++) == '\0')
					return (NULL);
			} while (sc != c);
			if (len > slen)
				return (NULL);
		} while (strncmp(s, find, len) != 0);
		s--;
	}
	return ((char *)s);
}

int	min(int a, int b) {
	return ((a < b) ? a : b);
}

int	max(int a, int b) {
	return ((a > b) ? a : b);
}

int	same_sign(int a, int b) {
	return ((a < 0 && b < 0) || (a > 0 && b > 0));
}

void test_char_ft(int (*org)(int), int (*ft)(int)) {
	int	i;
	int	ret_o, ret_y;

	printf("[int|unsigned char|expected|yours]\n");
	i = 0;
	while (i < 256) {
		ret_o = (*org)(i);
		ret_y = (*ft)(i);
		if (ret_o == ret_y)
			printf("G");
		else if (same_sign(ret_o, ret_y))
			printf("g");
		else
			printf("[%d|%c|%d|%d]", i, i, ret_o, ret_y);
		i++;
	}
	printf("\n");
}

char strupper_and_one(unsigned int idx, char c) {
	if (idx == 0) {
		return ('1');
	}
	return (ft_toupper(c));
}

int	_c_in_set(char c, char const *set) {
	int	i;

	i = 0;
	while (set[i])
		if ((unsigned char)set[i++] == (unsigned char)c)
			return (1);
	return (0);
}
//test atoi
int test_atoi(const char* str, int expected) {
    int result = ft_atoi(str);
    if (result == expected) {
        printf("Test PASSED for input '%s'\n", str);
        return 1;
    } else {
        printf("Test FAILED for input '%s': expected=%d, actual=%d\n", str, expected, result);
        return 0;
    }
}
//test bzero
void test_bzero(void* ptr, size_t len, void* expected) {
    ft_bzero(ptr, len);
    if (memcmp(ptr, expected, len) == 0) {
        printf("Test PASSED: %zu bytes set to 0 starting at address %p\n", len, ptr);
    } else {
        printf("Test FAILED: %zu bytes NOT set to 0 starting at address %p\n", len, ptr);
    }
}
//test calloc
void test_calloc(size_t nmemb, size_t size, void* expected) {
    void* ptr = ft_calloc(nmemb, size);
    if (memcmp(ptr, expected, nmemb * size) == 0) {
        printf("Test PASSED: allocated %zu elements of size %zu, expected content was found\n", nmemb, size);
    } else {
        printf("Test FAILED: allocated %zu elements of size %zu, but content did not match expected\n", nmemb, size);
    }
    free(ptr);
}
//test isalnum
void test_isalnum(int c, int expected) {
    int result = ft_isalnum(c);
    if (result == expected) {
        printf("Test PASSED: isalnum('%c') returned %d, expected %d\n", c, result, expected);
    } else {
        printf("Test FAILED: isalnum('%c') returned %d, but expected %d\n", c, result, expected);
    }
}
//test isalpha
void test_isalpha(int c, int expected) {
    int result = ft_isalpha(c);
    if (result == expected) {
        printf("Test PASSED: isalpha('%c') returned %d, expected %d\n", c, result, expected);
    } else {
        printf("Test FAILED: isalpha('%c') returned %d, but expected %d\n", c, result, expected);
    }
}
//test isdigit
void test_isdigit(int c, int expected) {
    int result = ft_isdigit(c);
    if (result == expected) {
        printf("Test PASSED: isdigit('%c') returned %d, expected %d\n", c, result, expected);
    } else {
        printf("Test FAILED: isdigit('%c') returned %d, but expected %d\n", c, result, expected);
    }
}
//test isascii
void test_isascii(int c, int expected) {
    int result = ft_isascii(c);
    if (result == expected) {
        printf("Test PASSED: isascii('%c') returned %d, expected %d\n", c, result, expected);
    } else {
        printf("Test FAILED: isascii('%c') returned %d, but expected %d\n", c, result, expected);
    }
}
//test isprint
void test_isprint(int c, int expected) {
    int result = ft_isprint(c);
    if (result == expected) {
        printf("Test PASSED: isprint('%c') returned %d, expected %d\n", c, result, expected);
    } else {
        printf("Test FAILED: isprint('%c') returned %d, but expected %d\n", c, result, expected);
    }
}
//test itoa
void	test_itoa(int c, char *expected)
{
    char result = *ft_itoa(c);
    if (result == *expected) {
        printf("Test PASSED: ft_itoa('%d') returned %c, expected %c\n", c, result, *expected);
    } else {
        printf("Test FAILED: ft_itoa('%d') returned %c, but expected %c\n", c, result, *expected);
    }
}
//test memchr
void test_memchr(void* ptr, int value, size_t num) {
    void* result = ft_memchr(ptr, value, num);
    if (result == NULL) {
        printf("Test FAILED: memchr returned NULL\n");
    } else {
        printf("Test PASSED: memchr returned address %p\n", result);
    }
}
//test memcmp
void test_ft_memcmp(const void *s1, const void *s2, size_t n, int expected_result) {
    int result = ft_memcmp(s1, s2, n);
    if (result == expected_result) {
        printf("PASSED\n");
    } else {
        printf("FAILED\n");
    }
}
//test memcpy
int test_memcpy() {
    char str1[20] = "hello world";
    char str2[20] = "";
    char str3[20] = "hello";
    char str4[20] = "";
    char str5[20] = "hello world";
    char str6[20] = "";
    char *ptr1, *ptr2, *ptr3;

    // Test case 1: Copy a string to an empty buffer
    ptr1 = ft_memcpy(str2, str1, strlen(str1) + 1);
    if (strcmp(str1, str2) != 0) {
        printf("Test FAILED: ft_memcpy() did not copy the string correctly\n");
        return 1;
    }
    if (ptr1 != str2) {
        printf("Test FAILED: ft_memcpy() did not return the destination pointer\n");
        return 1;
    }

    // Test case 2: Copy a string to a buffer that is too small
    ptr2 = ft_memcpy(str4, str3, strlen(str3) + 1);
    if (strcmp(str3, str4) != 0) {
        printf("Test FAILED: ft_memcpy() did not copy the string correctly\n");
        return 1;
    }
    if (ptr2 != str4) {
        printf("Test FAILED: ft_memcpy() did not return the destination pointer\n");
        return 1;
    }

    // Test case 3: Copy part of a string to another buffer
    ptr3 = ft_memcpy(str6, str5 + 6, 5);
    if (strcmp(str6, "world") != 0) {
        printf("Test FAILED: ft_memcpy() did not copy the string correctly\n");
        return 1;
    }
    if (ptr3 != str6) {
        printf("Test FAILED: ft_memcpy() did not return the destination pointer\n");
        return 1;
    }

    // All tests passed
    printf("All tests PASSED for ft_memcpy()\n");
    return 0;
}
//test memmove
void test_ft_memmove(void* dest, void* src, size_t size) {
    char* result = (char*) malloc(size);
    
    printf("Before ft_memmove: dest = %s, src = %s\n", (char*) dest, (char*) src);
    
    ft_memmove(dest, src, size);
    
    printf("After ft_memmove: dest = %s, src = %s\n", (char*) dest, (char*) src);
    
    free(result);
}

void test_ft_memmove1(void* dest, void* src, size_t size) {
    char* result = (char*) malloc(size);
    
    printf("Before memmove: dest = %s, src = %s\n", (char*) dest, (char*) src);
    
    memmove(dest, src, size);
    
    printf("After memmove: dest = %s, src = %s\n", (char*) dest, (char*) src);
    
    free(result);
}
//test memset
void test_ft_memset(void* ptr, int value, size_t num) {
    char* result = (char*) malloc(num);
    
    printf("Before ft_memset: ptr = %s\n", (char*) ptr);
    
    ft_memset(ptr, value, num);
    
    printf("After ft_memset: ptr = %s\n", (char*) ptr);
    
    free(result);
}
//test split
void test_ft_split(char const *s, char c) {
    char **result = ft_split(s, c);
    int i = 0;
    
    printf("Original string: %s\n", s);
    printf("Delimiter: %c\n", c);
    printf("Resulting substrings:\n");
    
    while (result[i] != NULL) {
        printf("%s\n", result[i]);
        i++;
    }
    
    free(result);
}
//test strchr
void test_ft_strchr(char *s, int c)
{
    printf("String: \"%s\", Character: '%c'\n", s, c);
    char *ft_result = ft_strchr(s, c);
    printf("ft_strchr Result: %s\n", ft_result ? ft_result : "NULL");
    char *result = strchr(s, c);
    printf("strchr Result: %s\n", result ? result : "NULL");
    
    if ((ft_result == NULL && result == NULL) || (ft_result && result && *ft_result == *result))
        printf("Test PASSED: ft_strchr() and strchr() returned the same result.\n\n");
    else
        printf("Test FAILED: ft_strchr() and strchr() returned different results.\n\n");
}
//test strdup
void	test_ft_strdup(const char *s1)
{
    char *s1_copy = strdup(s1);
    char *s2 = ft_strdup(s1);
    
    printf("Original String: %s\n", s1_copy);
    printf("ft_strdup Result: %s\n", s2);
    
    if (strcmp(s1_copy, s2) == 0)
        printf("Test PASSED: ft_strdup() and strdup() returned the same result.\n\n");
    else
        printf("Test FAILED: ft_strdup() and strdup() returned different results.\n\n");
    
    free(s1_copy);
    free(s2);
}
//test strjoin
void	test_ft_strjoin(const char *s1, const char *s2, const char *expected)
{
    char *result = ft_strjoin(s1, s2);
    
    if (strcmp(result, expected) == 0)
        printf("Test PASSED: ft_strjoin(\"%s\", \"%s\") returned \"%s\" as expected.\n", s1, s2, expected);
    else
        printf("Test FAILED: ft_strjoin(\"%s\", \"%s\") returned \"%s\", but expected \"%s\".\n", s1, s2, result, expected);
    
    free(result);
}
//test strlcat
void	test_ft_strlcat(char *dst, const char *src, size_t dstsize, size_t expected_return, char *expected_result)
{
    char *dst_copy = strdup(dst);
    size_t ret = ft_strlcat(dst, src, dstsize);
    
    printf("Source: %s, Destination: %s, Destination Size: %lu\n", src, dst_copy, dstsize);
    printf("ft_strlcat Result: %s, Return Value: %lu\n", dst, ret);
    
    if (ret == expected_return && strcmp(dst, expected_result) == 0)
        printf("Test PASSED: ft_strlcat() returned the expected result.\n\n");
    else
        printf("Test FAILED: ft_strlcat() did not return the expected result.\n\n");
    
    free(dst_copy);
}
//test strlcpy
void	test_ft_strlcpy(char *src, char *dst, size_t dstsize)
{
    char *src_copy = strdup(src);
    char *dst_copy = strdup(dst);
    
    printf("Source: %s, Destination: %s, dstsize: %ld\n", src_copy, dst_copy, dstsize);
    size_t ft_result = ft_strlcpy(dst, src, dstsize);
    printf("ft_strlcpy Result: %s, Return value: %ld\n", dst, ft_result);
    
    // Reset the dst_copy string to compare with the strlcpy() result
    memset(dst_copy, '0', strlen(dst_copy));
    size_t result = strlcpy(dst_copy, src_copy, dstsize);
    printf("strlcpy Result: %s, Return value: %ld\n", dst_copy, result);
    
    if (strcmp(dst, dst_copy) == 0 && ft_result == result)
        printf("Test PASSED: ft_strlcpy() and strlcpy() returned the same result.\n\n");
    else
        printf("Test FAILED: ft_strlcpy() and strlcpy() returned different results.\n\n");
    
    free(src_copy);
    free(dst_copy);
}
//test strlen
void test_ft_strlen(char *str)
{
    size_t expected_len = strlen(str);
    size_t ft_len = ft_strlen(str);

    if (expected_len == ft_len)
        printf("Test PASSED: ft_strlen(\"%s\") returned %lu, expected %lu\n", str, ft_len, expected_len);
    else
        printf("Test FAILED: ft_strlen(\"%s\") returned %lu, expected %lu\n", str, ft_len, expected_len);
}
//test strmapi
void	test_ft_strmapi(const char *str, char (*f)(unsigned int, char))
{
    char *result = ft_strmapi(str, f);
    printf("ft_strmapi(\"%s\", f):\n", str);
    printf("Result: %s\n", result);
    free(result);
}
char	ft_uppercase(unsigned int i, char c)
{
    if (c >= 'a' && c <= 'z')
        return (c - 'a' + 'A');
    return (c);
}
//test strncmp
void test_ft_strncmp(const char *s1, const char *s2, size_t n, int expected)
{
    int result = ft_strncmp(s1, s2, n);
    if (result == expected)
        printf("Test PASSED: ft_strncmp(\"%s\", \"%s\", %lu) = %d\n", s1, s2, n, result);
    else
        printf("Test FAILED: ft_strncmp(\"%s\", \"%s\", %lu) returned %d, expected %d\n", s1, s2, n, result, expected);

    // Also test the standard library strncmp() function to verify the result
    int standard_result = strncmp(s1, s2, n);
    if (standard_result == expected)
        printf("Test PASSED: strncmp(\"%s\", \"%s\", %lu) = %d\n\n", s1, s2, n, standard_result);
    else
        printf("Test FAILED: strncmp(\"%s\", \"%s\", %lu) returned %d, expected %d\n\n", s1, s2, n, standard_result, expected);
}

//test strnstr
void test_ft_strnstr(const char *haystack, const char *needle, size_t len, const char *expected_result)
{
    char *result = ft_strnstr(haystack, needle, len);

    if (result == NULL && expected_result == NULL)
        printf("Test PASSED: ft_strnstr(\"%s\", \"%s\", %zu) returns NULL as expected.\n", haystack, needle, len);
    else if (result == NULL || expected_result == NULL)
        printf("Test FAILED: ft_strnstr(\"%s\", \"%s\", %zu) returns NULL unexpectedly.\n", haystack, needle, len);
    else if (strcmp(result, expected_result) == 0)
        printf("Test PASSED: ft_strnstr(\"%s\", \"%s\", %zu) returns \"%s\" as expected.\n", haystack, needle, len, expected_result);
    else
        printf("Test FAILED: ft_strnstr(\"%s\", \"%s\", %zu) returns \"%s\" instead of \"%s\".\n", haystack, needle, len, result, expected_result);
}
//test strrchr
void test_ft_strrchr(char *str, int c)
{
    char *result1 = ft_strrchr(str, c);
    char *result2 = strrchr(str, c);

    if ((result1 == NULL && result2 == NULL) || (result1 && result2 && *result1 == *result2))
        printf("Test PASSED: ft_strrchr(\"%s\", %c) = \"%s\", strrchr(\"%s\", %c) = \"%s\"\n", str, c, result1, str, c, result2);
    else
        printf("Test FAILED: ft_strrchr(\"%s\", %c) = \"%s\", strrchr(\"%s\", %c) = \"%s\"\n", str, c, result1, str, c, result2);
}
//test strtrim
void	test_ft_strtrim(char const *s, char const *set, char const *expected)
{
    char *result = ft_strtrim(s, set);

    printf("Input string: \"%s\"\n", s);
    printf("Set of characters to remove: \"%s\"\n", set);
    printf("Expected result: \"%s\"\n", expected);
    printf("Result: \"%s\"\n", result);

    if (strcmp(result, expected) == 0)
        printf("Test PASSED: ft_strtrim() returned the expected result.\n\n");
    else
        printf("Test FAILED: ft_strtrim() did not return the expected result.\n\n");

    free(result);
}
//test substr
void test_ft_substr(char *s, unsigned int start, size_t len, char *expected)
{
    char *result = ft_substr(s, start, len);
    int comparison = strcmp(result, expected);
    if (comparison == 0)
        printf("Test PASSED: ft_substr(\"%s\", %u, %zu) = \"%s\"\n", s, start, len, result);
    else
        printf("Test FAILED: ft_substr(\"%s\", %u, %zu) returned \"%s\", but expected \"%s\"\n", s, start, len, result, expected);
    free(result);
}
//test tolower
void test_ft_tolower(int c)
{
    int res_libc = tolower(c);
    int res_ft_tolower = ft_tolower(c);
    
    if (res_libc == res_ft_tolower)
        printf("Test PASSED: ft_tolower(%c) = %c\n", c, res_ft_tolower);
    else
        printf("Test FAILED: ft_tolower(%c) returned %c, but expected %c\n", c, res_ft_tolower, res_libc);
}
//test toupper
void test_ft_toupper(char c)
{
    int expected = toupper(c);
    int result = ft_toupper(c);

    printf("Testing ft_toupper with character '%c':\n", c);
    printf("Expected result: %d\n", expected);
    printf("Actual result: %d\n", result);

    if (result == expected)
        printf("Test PASSED\n\n");
    else
        printf("Test FAILED\n\n");
}
//test ft_putstr_fd
void test_ft_putstr_fd(char *str, int fd)
{
    printf("Input string: \"%s\"\n", str);

    ft_putstr_fd(str, fd);
    printf("\n");

    fflush(stdout);
}
//test ft_putchar_fd
void	test_ft_putchar_fd(char c, int fd)
{
    ft_putchar_fd(c, fd);
    printf("\n");
}
//test ft_putendl_fd
void	test_ft_putendl_fd(char *str, int fd)
{
    printf("Input string: \"%s\"\n", str);
    ft_putendl_fd(str, fd);
}
//test ft_putnbr_fd
void test_ft_putnbr_fd(int n, int fd)
{
    printf("Number: %d\n", n);
    ft_putnbr_fd(n, fd);
    write(fd, "\n", 1);
}

int main(int argc, char const *argv[]) {
	int	j;
	(void) argc;
	(void) argv;
	int i;
	int memccpy_length = 0;
	char	str_dest[250] = "";
	char	str_ft_dest[250] = "";
	char	str_join_org[1024];
	char	*str_join_ft = NULL;

	/*
	atoi
	*/
	printf("---atoi---\n");

    int num_tests_passed = 0;

    num_tests_passed += test_atoi("123", 123);
    num_tests_passed += test_atoi("-456", -456);
    num_tests_passed += test_atoi("0", 0);
    num_tests_passed += test_atoi("2147483647", 2147483647);
    num_tests_passed += test_atoi("-2147483648", -2147483648);
    num_tests_passed += test_atoi("hello", 0);
    num_tests_passed += test_atoi("123abc", 123);
    num_tests_passed += test_atoi("abc123", 0);

    printf("Summary: %d tests passed.\n", num_tests_passed);

	/*
	bzero
	*/
	printf("\n---bzero---\n");

	char buffer[10];
    char expected[10] = {0};

    test_bzero(buffer, sizeof(buffer), expected);
    test_bzero(buffer + 3, sizeof(buffer) - 3, expected + 3);

	/*
	calloc
	*/
	printf("\n---calloc---\n");

    int expected_ints[5] = {0};
    double expected_doubles[10] = {0.0};
    char expected_chars[20] = {0};

    test_calloc(5, sizeof(int), expected_ints);
    test_calloc(10, sizeof(double), expected_doubles);
    test_calloc(20, sizeof(char), expected_chars);

	/*
	is_
	*/

	printf("\n---isalnum---\n");
	test_isalnum('A', 1);
    test_isalnum('a', 1);
    test_isalnum('0', 1);
    test_isalnum('$', 0);
    test_isalnum(' ', 0);

	printf("\n---isalpha---\n");
	test_isalpha('A', 1);
    test_isalpha('a', 1);
    test_isalpha('0', 0);
    test_isalpha('$', 0);
    test_isalpha(' ', 0);

	printf("\n---isascii---\n");
	test_isascii('A', 1);
    test_isascii('$', 1);
    test_isascii(' ', 1);
    test_isascii(128, 0);
    test_isascii(-1, 0);

	printf("\n---isdigit---\n");
	test_isdigit('0', 1);
    test_isdigit('9', 1);
    test_isdigit('A', 0);
    test_isdigit('$', 0);
    test_isdigit(' ', 0);

	printf("\n---isprint---\n");
	test_isprint('A', 1);
    test_isprint(' ', 1);
    test_isprint('\t', 0);
    test_isprint(127, 0);
    test_isprint(128, 0);

	/*
	itoa
	*/
	printf("\n---itoa---\n");
    test_itoa(0, "0");
    test_itoa(123, "123");
    test_itoa(-123, "-123");
    test_itoa(2147483647, "2147483647");
    test_itoa(-2147483648, "-2147483648");
	/*
	memchr
	*/
	printf("\n---memchr---\n");

	char str[] = "Hello, world!";
    char* ptr = &str[0];
    int value = 'w';

    // Test 1: Find a character that exists in the string
    printf("Test 1:\n");
    test_memchr(ptr, value, strlen(str));

    // Test 2: Find a character that doesn't exist in the string
    printf("Test 2: (if FAILED = PASSED) \n");
    test_memchr(ptr, 'z', strlen(str));

    // Test 3: Search for a character in a subset of the string
    printf("Test 3:\n");
    test_memchr(ptr + 7, value, strlen(str) - 7);

	/*
	memcmp
	*/
	printf("\n---memcmp---\n");


    char str1[] = "Hello, world!";
    char str2[] = "Hello, there!";
    char str3[] = "Hello, world!";
    char* ptr1 = &str1[0];
    char* ptr2 = &str2[0];
    char* ptr3 = &str3[0];

    // Test 1: Compare two identical strings
    printf("Test 1: ");
    test_ft_memcmp(ptr1, ptr3, strlen(str1), 0);

    // Test 2: Compare two different strings
    printf("Test 2: ");
    test_ft_memcmp(ptr1, ptr2, strlen(str1), -4);

    // Test 3: Compare a subset of two strings
    printf("Test 3: ");
    test_ft_memcmp(ptr1 + 7, ptr2 + 7, strlen(str1) - 7, 0);
	printf("If Test 2-3 FAILED = PASSED\n");

	/*
	memcpy
	*/
	printf("\n---memcpy---\n");
	int result = test_memcpy();	
	printf("%d\n", result);

	/*
	memmove
	*/
	printf("\n---memmove---\n");
    char str4[] = "Hello World!";
    char str5[] = "Bonjour";
    
    test_ft_memmove(str4 + 3, str4, strlen(str4) + 1);
    test_ft_memmove(str5, str5 + 3, strlen(str5) + 1);
    printf("\n");
    char str6[] = "Hello World!";
    char str7[] = "Bonjour";
    test_ft_memmove1(str6 + 3, str6, strlen(str6) + 1);
    test_ft_memmove1(str7, str7 + 3, strlen(str7) + 1);
 

	/*
	memset
	*/
	printf("\n---memset---\n");

    char str8[] = "Hello World!";
    char str9[] = "Bonjour";
    
    test_ft_memset(str8, '$', 5);
    test_ft_memset(str9 + 2, '#', 3);
	printf("\n");

	/*
	split
	*/
	printf("\n---split---\n");

	char to_split[10] = {'e', '.', 'w', 'u', '-', '+', ' ', '0', '2', '1'};
	char **splitted = NULL;
	int	k, l;
	int	out_length, total_length, sep_count;

	char str10[] = "Hello World!";
    char str11[] = "Bonjour,comment,allez-vous";
    
    test_ft_split(str10, ' ');
    test_ft_split(str11, ',');
	printf("\n");

	/*
	strchr
	*/
	printf("\n---strchr---\n");
    char s1[] = "Hello, world!";
    char s2[] = "";
    char s3[] = "aaaaaa";
    char s4[] = "ababab";
    char s5[] = "Testing 123";
    
    test_ft_strchr(s1, 'o');
    test_ft_strchr(s1, 'H');
    test_ft_strchr(s1, '!');
    test_ft_strchr(s2, 'a');
    test_ft_strchr(s3, 'a');
    test_ft_strchr(s3, 'b');
    test_ft_strchr(s4, 'b');
    test_ft_strchr(s4, 'a');
    test_ft_strchr(s5, 'T');
    test_ft_strchr(s5, ' ');
    test_ft_strchr(s5, '1');
    test_ft_strchr(s5, '4');

	/*
	strdup
	*/
	printf("---strdup---\n");

    char str13[] = "Hello world!";
    char str14[] = "Goodbye";
    char str15[] = "This is a test";
    
    test_ft_strdup(str13);
    test_ft_strdup(str14);
    test_ft_strdup(str15);

	/*
	strjoin
	*/
	printf("\n---strjoin---\n");
    test_ft_strjoin("", "", "");
    test_ft_strjoin("", "world", "world");
    test_ft_strjoin("Hello", "world", "Helloworld");
    test_ft_strjoin("Hello", " world", "Hello world");
    test_ft_strjoin("Hello ", "world", "Hello world");

	/*
	strlcat
	*/
	printf("\n---strlcat---\n");
	printf("\n---1P-2F-3F-4F-5F---\n\n");

	char str_lcat_org[2550] = "";
	int res_org = 0;
	char str_lcat_ft[2550] = "";
	int res_ft = 0;

    char str16[20] = "Hello";
    char str17[] = " world!";
    char str18[20] = "Goodbye";
    char str19[] = " cruel world!";
    char str20[] = "This is a long string that should be truncated.";
    
    test_ft_strlcat(str16, str17, 20, 12, "Hello world!");
    test_ft_strlcat(str16, str17, 6, 12, "Hello");
    test_ft_strlcat(str18, str19, 8, 17, "Goodbye ");
    test_ft_strlcat(str20, str17, 25, 37, "This is a long string that w");
    test_ft_strlcat(str20, str17, 10, 17, "This is a");

	/*
	strlcpy
	*/
	printf("\n---strlcpy---\n");

    char src1[] = "Hello";
    char dst1[10];
    char src2[] = "Goodbye";
    char dst2[4];
    char src3[] = "This is a test";
    char dst3[5];
    
    test_ft_strlcpy(src1, dst1, sizeof(dst1));
    test_ft_strlcpy(src2, dst2, sizeof(dst2));
    test_ft_strlcpy(src3, dst3, sizeof(dst3));

	/*
	strlen
	*/
	printf("\n---strlen---\n");

    char str21[] = "Hello world!";
    char str22[] = "";
    char str23[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Proin euismod velit sed dui rhoncus vestibulum.";

    test_ft_strlen(str21);
    test_ft_strlen(str22);
    test_ft_strlen(str23);
	/*
	strmapi
	*/
	printf("\n---strmapi---\n");

	char *str_mapi_ft = NULL;
	int all_upper;

    //const char *str = "Hello, world!";
    test_ft_strmapi(str, ft_uppercase);

	/*
	strncmp
	*/
	printf("\n---strncmp---\n");
	int	ncmp_ret;
	int	nft_cmp_ret;

    test_ft_strncmp("hello", "world", 3, 0);
    test_ft_strncmp("hello", "world", 2, 0);
    test_ft_strncmp("hello", "world", 10, -6);
    test_ft_strncmp("hello", "hello", 5, 0);
    test_ft_strncmp("hello", "helloworld", 5, 0);
    test_ft_strncmp("", "", 1, 0);
    test_ft_strncmp("a", "b", 1, -1);
    test_ft_strncmp("bbb", "aaaa", 2, 0);

	/*
	strnstr
	*/
	printf("\n---strnstr---\n");

    test_ft_strnstr("Hello, world!", "world", 13, "world!");
    test_ft_strnstr("Hello, world!", "world", 12, "world");
    test_ft_strnstr("Hello, world!", "world", 5, NULL);
    test_ft_strnstr("Hello, world!", "", 13, "Hello, world!");
    test_ft_strnstr("", "", 1, "");
    test_ft_strnstr("", "world", 5, NULL);
    test_ft_strnstr("Hello, world!", "planet", 13, NULL);
    test_ft_strnstr("This is a test", "is", 14, "is is a test");
	printf("\n");

	/*
	strrchr
	*/
	printf("\n---strrchr---\n");
    char str24[] = "Hello World!";
    char str25[] = "Another test string";
    char str26[] = "No matches";
    char str27[] = "Match at the end.";

    test_ft_strrchr(str24, 'l');
    test_ft_strrchr(str25, 't');
    test_ft_strrchr(str26, 'x');
    test_ft_strrchr(str27, '.');
    test_ft_strrchr(str27, 'e');
    test_ft_strrchr(str27, 'M');
	printf("\n");

	/*
	strtrim
	*/
	printf("\n---strtrim---\n");

	char set[10] = " .+-e103*";
	char *str_trim = NULL;

	i = 0;
    test_ft_strtrim("  Hello World!  ", " ", "Hello World!");
    test_ft_strtrim("\tGoodbye\t", "\t", "Goodbye");
    test_ft_strtrim("  \n\t  \n", " \n\t", "");
    test_ft_strtrim("    ", " ", "");
    test_ft_strtrim("", "abc", "");

	/*
	substr
	*/
	printf("\n---substr---\n");

    char str28[] = "Hello, world!";
    char str29[] = "Goodbye";
    char str30[] = "";
    char str31[] = "test";

    test_ft_substr(str28, 7, 6, "world!");
    test_ft_substr(str28, 0, 5, "Hello");
    test_ft_substr(str29, 0, 7, "Goodbye");
    test_ft_substr(str30, 0, 3, "");
    test_ft_substr(str31, 0, 0, "");

	/*
	to_
	*/
	printf("\n---tolower---\n");
    test_ft_tolower('A');
    test_ft_tolower('a');
    test_ft_tolower('Z');
    test_ft_tolower('z');
    test_ft_tolower('!');
    test_ft_tolower(' ');
    test_ft_tolower('5');
    test_ft_tolower('$');
    test_ft_tolower('\n');

	printf("\n---toupper---");
    test_ft_toupper('a');
    test_ft_toupper('A');
    test_ft_toupper('z');
    test_ft_toupper('Z');
    test_ft_toupper('!');
    test_ft_toupper(' ');
    test_ft_toupper('1');
    test_ft_toupper('$');
    test_ft_toupper('\n');
    test_ft_toupper('\t');
    test_ft_toupper('\0');

	/*
	ft_*_fd
	*/
	printf("\n---fd_functions---\n");

	printf("\n---ft_putchar_fd---\n");

    int fd = open("fd.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    
    if (fd == -1)
    {
        perror("Error opening file");
        return (1);
    }
    
    test_ft_putchar_fd('a', STDOUT_FILENO); // should print 'a' to stdout
    test_ft_putchar_fd('b', fd); // should write 'b' to output.txt

	printf("\n---ft_putstr_fd---\n");
	int fd1 = open("fd1.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    //int fd = 1; // Output to stdout

    // Test with empty string
    test_ft_putstr_fd("", fd1);

    // Test with non-empty string
    test_ft_putstr_fd("Hello world!", fd1);

	printf("\n---ft_putendl_fd---\n");
    // Test with standard output
    test_ft_putendl_fd("Hello, world!", 1);
    test_ft_putendl_fd("This is a test", 1);
    test_ft_putendl_fd("1234", 1);
    test_ft_putendl_fd("", 1);

    // Test with a file descriptor
    int fd2 = open("fd2.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    test_ft_putendl_fd("Testing ft_putendl_fd() with a file descriptor", fd2);
    
    printf("\n---ft_putnbr_fd---\n");
    int fd3 = open("fd3.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    test_ft_putnbr_fd(0, fd3);
    test_ft_putnbr_fd(123, fd3);
    test_ft_putnbr_fd(-456, fd3);
    test_ft_putnbr_fd(2147483647, fd3); // maximum value for a signed integer
    test_ft_putnbr_fd(-2147483648, fd3); // minimum value for a signed integer

	close(fd);
	close(fd1);
	close(fd2);
	close(fd3);
	return (0);
}