![Runtime](https://img.shields.io/badge/Runtime-2%20ms%20(beats%2050.75%25)-yellow?style=for-the-badge)
![Memory](https://img.shields.io/badge/Memory-8.72%20MB%20(beats%2020.79%25)-orange?style=for-the-badge)

---

## Problem Explained

A **palindrome** is a number that reads the same backward as forward. 

This problem asks you to take an integer `x` and return `true` if it is a palindrome, and `false` if it is not.

*   `121` is a palindrome because reversing `121` gives `121` (matches).
*   `-121` is **not** a palindrome because reversing `-121` gives `121-` (the negative sign moves to the end).
*   `10` is **not** a palindrome because reversing `10` gives `01` (which is just `1`).

---

## Intuition

To check if a number is a palindrome without converting it into text, you can reverse the number mathematically and compare it to the original.

You extract digits from right to left using two basic math operations:
1. **Modulo (`x % 10`)**: Gives you the last digit of `x`.
2. **Integer Division (`x / 10`)**: Drops the last digit from `x`.

By popping digits off the end of `x` and pushing them onto a new number (`rev`), you rebuild the number in reverse. If the reversed result matches the starting number, it is a palindrome.

Negative numbers can never be palindromes because the minus sign stays at the front, so you can reject them immediately.

---

## Approach

Here is how the given code executes step-by-step:

*   **Reject negative numbers:** Check if `x < 0`. If it is negative, immediately return `false`.
*   **Save the original value:** Create a copy of `x` called `n` using the `long` type. This keeps a backup of the original number so you can compare it later.
*   **Set up a reverse variable:** Create `rev = 0` (also a `long`) to build the reversed number.
*   **Reverse the number in a loop:** While `x` is not `0`:
    *   Get the last digit of `x` using `x % 10`.
    *   Shift `rev` left by multiplying it by 10, then add the extracted digit (`rev = rev * 10 + x % 10`).
    *   Remove the last digit from `x` using integer division (`x /= 10`).
*   **Compare results:** After the loop finishes, check if `rev` is equal to `n`. Return `true` if they match, and `false` if they do not.

---

## Time & Space Complexity

**Current Complexity:**
*   **Time:** **O(log₁₀(n))** — In each loop step, we divide `x` by 10. The loop runs once for every digit in the number.
*   **Space:** **O(1)** — We only use a few extra variables (`n`, `rev`), so extra memory does not grow with the input size.

### Can this be improved?

Yes! While the theoretical time complexity remains the same, you can double the practical speed and eliminate the need for `long` variables by **reversing only half of the number**.

If a number is a palindrome, its left half and right half must mirror each other. You can stop reversing once your reversed number becomes greater than or equal to the remaining half of `x`.

Here are the key changed lines:

```cpp
// Negative numbers and non-zero numbers ending in 0 (like 10, 100) are not palindromes
if (x < 0 || (x % 10 == 0 && x != 0)) {
    return false;
}

int rev = 0;
// Reverse only half of the digits
while (x > rev) {
    rev = rev * 10 + x % 10;
    x /= 10;
}

// For even digits: x == rev (e.g., 1221 -> x = 12, rev = 12)
// For odd digits: x == rev / 10 to ignore middle digit (e.g., 12321 -> x = 12, rev = 123)
return x == rev || x == rev / 10;
```

**Improved Complexity:**
*   **Time:** **O(log₁₀(n))** — Runs in half the iterations of the full reversal approach.
*   **Space:** **O(1)** — Uses plain `int` values and no extra memory.

**Theoretical Best:** **O(log₁₀(n))** time and **O(1)** space. The half-reversal approach achieves this optimal bound cleanly.

---

## Edge Cases Handled

*   **Negative numbers (`x < 0`):** Handled by returning `false` at the very beginning.
*   **Single-digit numbers (`0` to `9`):** Handled correctly. The loop runs once, `rev` matches `n`, and it returns `true`.
*   **Numbers ending in `0` (e.g., `10`, `100`):** The code reverses `10` to `1`. Since `1 != 10`, it correctly returns `false`.
*   **Large numbers (near 32-bit limits):** Reversing a 32-bit integer can cause an integer overflow error. The original code safely prevents this by declaring `rev` as a 64-bit `long`.
