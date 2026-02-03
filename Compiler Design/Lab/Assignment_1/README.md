# README


## How to run
- `g++ "RE_to_NFA_and_DFA.cpp"`
- `./a`
- Otherwise, just run the **RE\_to\_NFA\_and\_DFA.exe** file and then give inputs.


## Input format
- Just one line of string i.e. the Regular Expression (without spaces).
- Each character from the expression apart from the operators.
- Only use the operators: + (Union) \* (Kleene Star) () (Parenthesis).


## Output format
- Output is a Directed-graph printed as a list of edges (q1,q2,w).
- This means the state transitions from q1 -> q2, upon the input symbol w.
- "q_i", "q_f" are the start and final state respectively of NFA.
- "S" is the start state and "F1", "F2", ... are the final states of DFA. 
- 'ε' is output as 'E' in terminal.
- Note that the DFA generated here is already min-DFA by virtue of construction.


## Simulation
- Paste individual outputs (NFA and DFA) separately from "output.txt file" in :- 
- [Another Graph Editory](https://anacc22.github.io/another_graph_editor/)
    - Paste data in the 'Edges' section.
    - Use for DFA (or smaller graphs).
    - Turn ON 'Directed' option. Ensure 'Multiedge Mode' option is ON.
    - Click on 'Appearance' and increase 'Edge Length' bar. Turn ON 'Components' (optional).
- [Graph Editor](https://csacademy.com/app/graph_editor/)
    - Paste data in 'Graph Data' section.
    - Use for NFA (or larger graphs).
    - Choose 'Directed' option. Can't support multi-edges.
    - Go to 'Config' and set 'Node radius' to 13 and 'Edge ideal length' to 90.

- This will generate a graph corresponding to NFA/DFA.
- Adjust other settings as per convenience for better visibility.

**NOTE** - Since self-loops are not supported in the Graph Simulation website. Hence self-loop from say (u-u, a) is shown as (u-(blank), a)+((blank)-u, a)


## Examples: [Source](https://www.tutorialspoint.com/what-is-the-conversion-of-a-regular-expression-to-finite-automata-nfa)
- Input 1: a(a+b)*ab
- Input 2: a+ab+b
- Input 3: a(b+c)*
- Input 4: (0+1)*1(0+1)
