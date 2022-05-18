# Results

### The Textbook Implementation

```c
u64 xorshift(ShiftState *state) {
    u64 t = state -> x[0];
    u64 s = state -> x[1];
    state -> x[0] = s;
    t ^= t << 23;
    t ^= t >> 18;
    t ^= s ^ (s >> 5);
    state -> x[1] = t;
    return t + s;
}
```

This is the textbook implementation for the xorshift+ random number generation algorithm, taken straight from the [Xorshift page on Wikipedia.](https://en.wikipedia.org/wiki/Xorshift)

The default implementation performed very well on all tests that I conducted. It has a low average chi-score of about 250, a very small average squared difference between the actual distribution of numbers and the expected distribution of numbers of 0.000017, an average absolute distance between numbers of 0.333349 (extremely close to the expected 0.3333333 of a fully random distribution of numbers),and an average signed square distance between numbers of 0.229536, a number small enough to suggest that there is no correlation between the direction a number shifts and the amount the number shifts by.

### Implementations 1 - 4

The results for these implementations were surprisingly boring.

I thought that by changing the shift parameters of the function, there would be radical changes in the randomness of the numbers and the distribution of the numbers, but most of the alternative implementations performed just as well as the textbook implementation.

Take alternative implementation #3 as an example:

```c
u64 xorshiftAlt3(ShiftState *state) {
    u64 t = state -> x[0];
    u64 s = state -> x[1];
    state -> x[0] = s;
    t ^= t << 8; // 23
    t ^= t >> 11; // 18
    t ^= s ^ (s >> 2); // 5
    state -> x[1] = t;
    return t + s;
}
```

The parameters were changed drastically, with the left shift from 23 to 8, the right shift from 18 to 11, and the final shift with the stored state from 5 to 2.

However, that implementation performed just as well as the textbook xorshift+ implementation from Wikipedia: The average chi squared score were within 0.5 points of one another, the average-average squared difference between actual and expected values are about 0.000017, and the average distance between numbers, 0.333266, (the metric that I expected to change the most in between implementations,) were barely different from the expected 0.333333.

The same story goes for implementation 1, 2, and 4.

### Implementation 5

The story changes however, when we get to implementation 5, the implementation with the most extreme changes to its parameters.

```c
u64 xorshiftAlt5(ShiftState *state) {
    u64 t = state -> x[0];
    u64 s = state -> x[1];
    state -> x[0] = s;
    t ^= t << 2; // 23
    t ^= t >> 49; // 18
    t ^= s ^ (s >> 24); // 5
    state -> x[1] = t;
    return t + s;
}
```

The right shift was changed from 23 to 2, the left shift from 18 to 49, and the stored state shift from 5 to 24.

Implementation 5 had an extremely high chi score of approximately 32997, more than 130 times the score of all the other implementations. The average distance between numbers in implementation 5 is only about 0.29, more than 0.04 points away from the expected value of 0.333333. The average squared distance between actual and expected values is a high 0.0042, (compared with the 0.000017 for all the other implementations) meaning that there are noticeable gaps and clusters in the distribution of values that it generates.

### Other Tests For Randomness and Random Number Generation

In this project, I've only implemented 4 tests for randomness, a chi squared test to test for a rough uniform distribution, a comparison of the actual distribution to an expected distribution of values, and two tests that analyze the distances between two adjacent randomly generated numbers. 

In reality, there are much more tests we need to conduct if we wanted to test for the randomness of numbers. For example, many random number generators have flaws in the lower bits of the numbers that they generate, and our tests above are designed to only test for randomness in the higher bits. (The lower bits do not have significant effects on the magnitudes of our numbers ( eg: 0.123456 vs 0.123457 ), so possible non-randomness in our lower bits will elude the tests above.)

To test for this, one can reverse the binary representation of the numbers and conduct the same tests above for that "reversed" number. Perhaps I can implement such a test in the future.

Apart from randomness, other metrics should also be analyzed to determine the strength of a random number generator. One such metric is the **period** of our random number generator, which is how many numbers our random number generator can generate, given an initial state, before it goes through all possible numbers and returns back to that original state (where and when it will then generate the same cycle of numbers all over again).

### Conclusion

Unfortunately, the results of this project / study weren't as interesting as I had hoped for it to be, but really, that's a wonderful thing! It just goes to show the resiliance and viability of the xorshift+ algorithm, no matter the changes to it's parameters.

Even the 5th implementation, which has an assortment of problems, can still probably be used for a random number generator in something like a video game, without it's players noticing any obvious flaws or patterns in the numbers that it generates. The other four implementations work just as well (or almost as well, for the 4th implementation) as the original one, and can probably subsitute the textbook implementation without causing any problems.

And that concludes my study. Thanks for reading, and have a wonderful day.
