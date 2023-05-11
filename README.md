Arduino ButtonSlim Library
===

This Arduino libary uses a single button for input. <br>
The button gets debounced.

This library is a slimmed down version of ButtonOne,<br>
with the aim of reducing the RAM usage, by eliminating every option<br>
beyond the btnPress function.

- No BottonRelease option
- No LongPress option
- No RepeatPress option
- No ToggleButton option

By eliminating these options, each ButtonSlim instance only uses 12 bytes of RAM<br>
where each instance of ButtonOne uses 41 bytes of RAM, but also offers more functionality.

It is possible to use both ButtonSlim and ButtonOne button declarations in the same sketch,<br>
so long as both button libraries are present in your 'Arduino/libraries' folder