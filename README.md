# PODEM-Algorithm-Implementation
The objective of the project is to implement in C programming language the PODEM algorithm to generate test vectors for a given fault

The tool will detect all the detectable faults and provide the corresponding test vectors for each fault. The inputs will be circuit structures and fault list with size two times the number of nodes. All faults are single stuck at faults chosen one at a time.


## Algorithm

The basic flow of PODEM is illustrated in the flowchart. Although it is a deterministic search algorithm, the decisions are limited to the primary inputs. All internal signals obtain their logic values by means of logic simulation from the decision points. As a result, no conflict will ever occur at the internal signals of the circuit. The only possible conflicts in PODEM are either (1) the target fault is not excited or (2) the D-frontier becomes empty. In either of these cases, the search must backtrack. The algorithm examines all the possible input values till a test is found for a given fault. Initially all the primary inputs are unassigned, these inputs are assigned values one by one depending on the fault location and fault type (s-a-0 or s-a-1), the path chosen for fault propagation also determine the input assignment. The implications of primary inputs are evaluated every time a new value is assigned to an input. These implications are used to determine testability of the faults. If any input does not contribute in fault detection, then it is dropped from the input list. So the algorithm basically assigns primary inputs with different values sequentially till a test vector for a given fault is found.


## Output 

Logic Ssmulations are stored into the ".response" Files

Test Patterns are stored into the".Pattern" Files
