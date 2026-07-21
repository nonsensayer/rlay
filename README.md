# A very simple rectange 'layouting'

Don't think of this library a lot, it is really simple concept! It's just some
utility functions to split rectangles into parts and have some kind of system
to keep track of them instead of totally hardcoding everything.

I might add some additional features later, but this is kind of all this system
needs, I would even say, it is not a system.

# Why?

Initial idea came from me playing Stormworks, there you can write Lua scripts
for automation and with that -- draw user interfaces on monitors. And lately I
am thinking where to apply and test this system, so it might be useful to put
everything in one place here.

# Dependencies?

None if you redefine `RLAY_assert` or it will be only `assert.h`.
