# PS1: LFSR / PhotoMagic

## Contact
Name: Patricia Antlitz

Section: 202

Time to Complete: Im sorry, I didn't keep track of time


## Description
Explain what the project does.

This project uses the LFSR (Linear Feedback Shift Register) machine simulator built for project PS1a. It works on a binary code which is a Fibonacci sequence. We shift all bits to the left by one, and use the required tap positions and the MSB (Most Significant Bit) to calculate the next bit, to be added to the end of the string. 

It uses this binary number generated by the LFSR machine as a seed that is used to generate a random
color. This color is used to substitute the color of an image's pixels. That encrypts the image by
making it unrecognizable. 
The image to be encrypted is an existing image saved in the directory. The program is ran by passing the following arguments: ./PhotoMagic existing_image.png new_image.png 1011011000110110
The new, encrypted image is saved in the directory. If the program is ran again passing the new, encrypted image's name first, the image will be decrypted and reverted to the original image.


### Features
Describe the representation you used and why you did things that way.

I originally changed the method step() from ps1a to accommodate both the LFSR and the image encryption. I did that because as it is, I had to change that method in order to get it to change the pixel's colors as expected. After running my tests I realized that I had many errors when testing the LFSR. I think maybe it would have been ok to just get rid of those tests and just disregard the whole LFSR thing altogether but I didn't spend hours doing that in preparation for this just to get rid of it. So I kept it, and instead I modified step() by adding a boolean parameter which checks if the seed that is being generated is being generated for an image encryption, or a LFSR simulation. "true" is an image, "false" is an bit shift for LFSR. There is an if statement there that handles the XOR calculation depending on what the program is trying to do. So it worked both ways.
However, I got errors after submitting, because I was missing step(). So, although I think its not ideal, I had to separate the methods. I created a similar method called stepColors() instead.

PhotoMagic transform:
It iterates through every pixel in row major order. Then it gets the color of every pixel. It used the step(bool) method to generate a 8-bit numbers that represents a color. those values are added to the red, green and blue components. Then we XOR the color components with the new color generated, and then we set the current pixel's color with that colors. The seed must be 16bit to decrypt.

### Issues
What doesn't work.  Be honest.  You might be penalized if you claim something works and it doesn't.

When I started working on this project something happened to my virtual machine and I suddenly lost all my apps. I didn't even have firefox to search online or download the apps again. I tried to restore the machine with no success. After researching online I read my VMware Fusion virtual machine needed to be updated to work, but I recently updated my macOS to Sonoma and the new version of VMware is not comparable with that, yet.
I had a free version of the software (the older version), so their platform wouldn't let me download that version of VMware again (you can download and install only once). I had to install VirtualBox instead.
After I did that I installed ubuntu and did all the setup from ps0 again. I stated the code again, and the machine froze on me because I forgot to clean all my caches that have been pilling up on me for forever now. So, since it was frozen I clicked on "restore" machine, and that broke everything. I lost my code again and I had to install ubuntu again and do all the setup..............again. 
So, when it comes to issues that was the worse issue I faced while working on this project. I lost my code twice. Don't worry though, I learned my lesson. I have been taking snapshots of my current machine state every hour or so just in case, and I am saving my code on my google drive just in case.

In terms of the code, every time I run the program I get this message: "Setting vertical sync not supported". I read online I should adjust my V-Sync but I didn't find anything useful to actually implement something that would fix that problem. Im not quite sure what that is and if its a system problem.

The test file has a method called compareImages. Ideally I wanted to use operator overload to compare the images. I tried to implement that, in the namespace PhotoMagic, and then the FibLFSR class but I just couldn't figure it out. I think I just didn't know where to place it to make it work because the logic looked fine to me. So I created this method that compares the pixels

My plan was to embed the seed inside the image using metadata. Then the same seed would be needed to decrypt the image. I would have done it if I wasn't one week late already.

### Tests
Describe what is being tested in your Boost unit tests.

This code is running a stress test, when a lot of bits are being generated. The idea is to see if the program is able to handle it. On top of the stress test, following the same idea, there is a performance test. This test checks if the program is efficient. There is a test that checks if the seed is a binary number, and a test that checks what the output would be if the seed was smaller, and if it followed certain pattens, such as 111111, or 000000. There is also a test that checks how consistent the outputs are. No destructors were needed, because no memory was allocated.

There is a test that tests the encryption and decryption of an image
There is one that tests the encryption if different seeds were given
another one tests the encryption of a very small image 1x1
and one that tests the encryption of a very large image
following that there is a test for boundaries, using small seeds and large seeds
the last test tests if the image is a png

### Extra Credit
Anything special you did. This is required to earn bonus points.
I didn't do anything special, sorry

## Acknowledgements
List all sources of help including the instructor or TAs, classmates, and web pages.

sources ps1b:

*class materials

encrypt images:
https://en.sfml-dev.org/forums/index.php?topic=7323.0

https://en.sfml-dev.org/forums/index.php?topic=7323.15

also, back to this, same source from ps1a:
https://github.com/qiaoyuguo/practice/blob/master/cos126/assignments/assign5/LFSR.java


Pixel colors:

https://en.sfml-dev.org/forums/index.php?topic=4210.0

https://stackoverflow.com/questions/51256740/how-to-get-the-color-of-a-pixel-in-an-image-in-c-sfml

https://www.gamedev.net/forums/topic/693835-sfml-and-fast-pixel-drawing-in-c/

namespace:

https://learn.microsoft.com/en-us/cpp/cpp/namespaces-cpp?view=msvc-170

https://en.cppreference.com/w/cpp/language/namespace

main arguments:

https://www.geeksforgeeks.org/command-line-arguments-in-c-cpp/


sources from ps1a:

studying:
https://www.eetimes.com/tutorial-linear-feedback-shift-registers-lfsrs-part-1/

https://en.wikipedia.org/wiki/Linear-feedback_shift_register

bitset:
https://en.cppreference.com/w/cpp/utility/bitset

online calculator, to check outputs:
https://www.omnicalculator.com/math/linear-feedback-shift-register

polynomial lfsr example coded in C: and example 
https://www.moria.us/articles/demystifying-the-lfsr/

source: 
https://cs.stackexchange.com/questions/109618/how-fibonacci-lfsr-work

https://www.programiz.com/cpp-programming/examples/fibonacci-series

This is the example that made me realize strings were the best option:
https://github.com/qiaoyuguo/practice/blob/master/cos126/assignments/assign5/LFSR.java

other code sources:
https://github.com/hamolicious/LFSR-RNG/blob/main/lfsrrng/generator.py




