This small application demonstrates a significant performance issue of Nvidia's Quadro M6000 12GB and Titan Xp video cards with WGL window setup under Windows 8.1 Pro 64 bit and Windows 10 Enterprise 64 bit.

* Might also apply to other configurations, these are the ones that have been tested.

As soon as WGL's ChoosePixelFormat or SetPixelFormat is called, memory allocation will be excruciatingly slow for the entire lifetime of the process, even if no OpenGL context or any kind of GPU computing is used.
