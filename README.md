# Sick Rays

## Description
We Implemented a ray tracer in C. We simulated light particles bouncing off an STL object with material properties in order to create a rendered, realistic image of that object. We created beautiful images of STLs using our ray tracer, and can do the same for any STL imputed into the program. Learn more about our project at our [project site](https://maxschommer.github.io/SoftSys_Terminally_Eeeel).

## Authors
* [Max Schommer](http://www.maxschommer.com/)
* [Jeremy Garcia](https://github.com/jag-123)
* [Rachel Yang](http://rachelyang02.github.io)
* [Bill Du](https://github.com/DHZBill)

## Getting Started 
Download the finals folder and compile the Makefile by running `blah`.

## Usage
The STL files used must have ASCII STL format.

The output from our ray tracer will be a series of .ppm files, which can then be compiled into a video by running `convert image*ppm sick_rays.gif` while inside the same folder as the images. You can also follow [this process](http://jupiter.ethz.ch/~pjt/makingMovies.html) to compile the .ppm files into a video.

## License
MIT License

Copyright (c) 2017 SoftsysTerminallyEeeel

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
