A dumb compiler for a subset of awa5.0, targetting x86.

There are two frontends for Awa5.0, one targeting awatalk and the other targeting 
awassembly, where I call awassembly the shorthand notation of awatalk.

Compiler Passes:

Awatalk (.awa files) / Awassembly (.awasm files) -> Binary IR -> Tokens -> Backend -> X86

//---------------------------------------------------------------/

Backend Passes:

TODO
