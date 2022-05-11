# Analysis of The Xorshift+ Random Number Generator

### AP Statistics Final Project

So I was creating a game using C, and I needed a way to generate some random numbers between 0 and 1. At first, I used C's rand() function, but I noticed that it isn't "random" and only has a specific set of values (32768 to be exact). I decided to go and see if I could find a better algorithm for random number generation.

I went online and did some reading about the implementations of random number generators in various programming languages. Specifically, I was interested in the JavaScript implementation of its Math.random() function. It turns out that most modern browsers use an algorithm called xorshift for their Math.random() functions.

Wikipedia reveals several variants of the xorshift algorithm. In this project, I'll be using the xorshift+ algorithm, which is both performant and passes various "randomness" tests. To test how random the algorithm actually is, I'll run several of my own tests on it, as well as create slightly modified and alternative versions of the algorithm and testing those too to see how it compares with the textbook implementation.

## Implementations

The default xorshift() implementation was taken straight from [Wikipedia](https://en.wikipedia.org/wiki/Xorshift).

If you look at the algorithm, you'll see that specific parameters are used for it's bitshifts. To test if those parameters generate good results and are the best parameters for generating random number generators, I'll create alternative implementations where I modify the bitshift parameters and compare them with each other to see which one is the most "random."

## Testing for Randomness

I've devised a few tests in order to test for "randomness."

### Test One: Testing for Uniformity

First, a random number generator is designed to give a uniform distribution of random numbers, in this case, between 0 and 1. This means that in repeated generating of these random numbers, we every number to appear as frequently as every other number, and when we graph the frequencies of all of our numbers, we should get a uniform distribution where the frequencies are roughly the same.

Now, due to the nature of these random floating point numbers we are generating, we can't just simply look at a graph of the frequencies of these numbers. Floating point numbers are not part of a discrete set of values. They are continuous.* Therefore, it is necessary for us to look at RANGES of numbers, and how many numbers are part of that range, rather than just the frequency of those numbers. Since we are generating 10000 numbers for each implementation, I think it'll be appropriate to split up the range from 0 to 1 into 250 separate ranges, with 40 numbers within each range.

\* It is to note that due to the way floating point numbers are represented in computers, one could argue that in computer science, floats ARE actually discrete numbers. However, due to the sheer size of all these floats, we'll treat them as if they are continuous anyway.

We will compare the sum of the squared distances between the actual count and the expected count, divided by the expected count. Sounds familiar? Yeah, it's a chi squared test. However, it is to note that this test will probably not be that insightful since even the worst of random number generators can give us a relatively low chi squared statistic, and compared to how many degrees of freedom we have (249) we'll probably get all 1s for our p values. However, we can still compare the statistic with one another, and see which algorithm scored the best, although again, it doesn't really say much as the score can fluctuate, and they're all supposed to be pretty low anyway.

### Test Two: Comparison of Distribution to Expected Values

The second test is very similar to the first one, except in this test, we're going to use the line y = x / 10000 to simulate a perfectly uniform distribution and then comparing the data that we get from our random number generators to our expected value from that line.

The x value is our `i` counter, which goes from 0 to 10000.

The y value will be the ith element of the array of all of our 10000 randomly generated numbers, sorted from low to high.

An example RNG data point will look something like this: ( 7149, 0.70941372070736175015 )

Meanwhile, our simulated data point based on the line will look like this: ( 7149, 0.7149 )

We'll go through each of our RNG data points, find the squared difference in distances between the actual distances with the simulated difference, and then sum up all these differences. Similar to the first test, this test is designed to help us test the uniformity of the distribution, and make sure that our RNG has good coverage on all numbers.

For example, if our RNG gives us something like 0.665 0.665 0.665 0.666 0.667 0.667 0.667 0.667 0.694 where it stalls at a specific range of numbers and then suddenly advances to another number, this RNG will pass our first test, but will definitely perform worse on this one.

### Test Three: Distances Between Two Numbers

The last test I'll conduct will be a unique and telling one: I'll compare the signed square distance and the average absolute distance between two randomly generated numbers.

These metrics are important because it checks the predictability of a number based on the previous number. Additionally, while all the other tests check only the final set of numbers, this test will instead check for independence between one number and the other.

#### Signed Square Distance

The signed square distance is the square distance between one number and the other, then signed to give us information about the direction it's travelling. This metric will tell us about any significant association between the direction a number is going, and it's next number.

If our number tends to advance up in small intervals but advance down in bigger ones, for example 0.1, 0.11, 0.12, 0.1, then we'll get a negative number for our average signed square distance. ( 0.01 * 0.01 + 0.01 * 0.01 - 0.02 * 0.02 = 0.0002 - 0.0004 = -0.0002 )

If our number tends to advance down in small intervals but advance upu in bigger ones, then we'll get a positive number.

If our number tends to advance down and advance up in roughly equal steps and roughly equal frequencies, then we'll get a number close to 0.

#### Average Absolute Distance

The average absolute distance is the average distance between two random numbers, unsigned. This metric will help us determine if there is any significant association between one number and the next.

For example, a random number generator that gives us 0.00, 0.01, 0.02, ... 0.98, 0.99 will pass both the first and second test with flying colors, but because the average absolute distances between them is only 0.01, we'll know that there's something very wrong with that generator.

So what is the average absolute distance you ask? It's 1/3. I don't really know for certain, but [according to my simulation,](./avg_abs_dist.txt) it should be 1/3, or at least a number very close to 1/3.

## Results

## Learn More

[Xorshift](https://en.wikipedia.org/wiki/Xorshift)
