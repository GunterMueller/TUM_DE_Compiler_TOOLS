{ pascal.g :
  erstellt 3.3.89 aus der Datei grammars/pascal/gram.y aus "Fish-Disk" Nr. 156
  An MiniMUG-Format angepasst, verschiedene Teile in Scanner ausgelagert

 *
 * Pascal grammar in Yacc format, based originally on BNF given
 * in "Standard Pascal -- User Reference Manual", by Doug Cooper.
 * This in turn is the BNF given by the ANSI and ISO Pascal standards,
 * and so, is PUBLIC DOMAIN. The grammar is for ISO Level 0 Pascal.
 * The grammar has been massaged somewhat to make it LALR, and added
 * the following extensions.
 *
 * constant expressions
 * otherwise statement in a case
 * productions to correctly match else's with if's
 * beginnings of a separate compilation facility
}

{ Deklarationen der Terminalsymbole in Uebereinstimmung mit pascal.scb }
terminals

1 ADDOP          
2 ARRAY 
3 ASSIGNMENT 
4 BEGIN 
5 CASE 
6 CHARACTER_STRING 
7 COLON 
8 COMMA 
9 CONST 
10 DIGSEQ
11 DO   
12 DOT 
13 DOTDOT 
14 DOWNTO 
15 ELSE 
16 END 
17 EQUAL 
18 EXTERNAL 
19 tFILE 
20 FOR 
21 FORWARD 
22 FUNCTION
23 GOTO 
24 IDENTIFIER 
25 IF 
26 tLABEL 
27 LBRAC 
28 LPAREN 
29 MULOP  { "*" = 1 , "/" = 2 , "AND" = 3 , "DIV" = 4 , "MOD" = 5 } 
30 NIL 
31 NOT
32 OF 
33 OTHERWISE 
34 PACKED 
35 PROCEDURE 
36 tPROGRAM 
37 RBRAC
38 REALNUMBER 
39 RECORD 
40 tRELOP    {  ">=" = 2 , ">" = 3 , "<=" = 4 , "<" = 5 , "<>" = 6 , "IN" = 7 }
41 REPEAT 
42 RPAREN 
43 SEMICOLON 
44 SET 
45 STARSTAR 
46 THEN
47 TO 
48 TYPE 
49 UNTIL 
50 UPARROW 
51 VAR 
52 WHILE 
53 WITH

{actions boese}

axiom    file

rules

file -> { 1 } program;
        { 2 } module.

program -> { 3 } program_heading semicolon block DOT .

program_heading -> { 4 } tPROGRAM identifier;
        { 5 } tPROGRAM identifier LPAREN identifier_list RPAREN.

identifier_list -> { 6 } {boese} identifier_list comma identifier;
                   { 7 } identifier;
                   { 8 } EMPTY.

block -> { 9 }  label_declaration_part
        constant_definition_part
        type_definition_part
        variable_declaration_part
        procedure_and_function_declaration_part
        statement_part
        .

module -> { 10 } constant_definition_part
        type_definition_part
        variable_declaration_part
        procedure_and_function_declaration_part
        .

label_declaration_part -> { 11 } tLABEL label_list semicolon;
                          { 12 } EMPTY.

label_list -> { 13 } label_list comma label;
              { 14 } label;
              { 15 } EMPTY.

label -> { 16 } DIGSEQ.

constant_definition_part -> { 17 } CONST constant_list;
                            { 18 } EMPTY.

constant_list -> { 19 } constant_list constant_definition;
                 { 20 } EMPTY.

constant_definition -> { 21 } identifier EQUAL cexpression semicolon .

cexpression -> { 22 } csimple_expression;
               { 23 } csimple_expression relop csimple_expression.

csimple_expression -> { 24 } cterm;
                      { 25 } csimple_expression addop cterm.

cterm -> { 26 } cfactor ;
         { 27 } cterm mulop cfactor .

cfactor -> { 28 } sign cfactor;
           { 29 } cexponentiation.

cexponentiation -> { 30 } cprimary;
                   { 31 } cprimary STARSTAR cexponentiation .

cprimary -> { 32 } identifier ;
            { 33 } LPAREN cexpression RPAREN ;
            { 34 } unsigned_constant ;
            { 35 } NOT cprimary .

constant -> { 36 } non_string;
            { 37 } sign non_string;
            { 38 } CHARACTER_STRING {  ;
            cexpression } .         { good stuff! }

sign -> ADDOP.  { ACHTUNG : OR muss im Semantikteil ausgeschlossen werden !!! }

non_string -> DIGSEQ ;
              identifier ;
              REALNUMBER.  { ACHTUNG : vom Scanner noch nicht geliefert }
        
type_definition_part -> TYPE type_definition_list;
                        EMPTY .

type_definition_list -> type_definition_list type_definition ;
                        type_definition.

type_definition -> identifier EQUAL type_denoter semicolon .

type_denoter -> identifier ;
                new_type .

new_type -> new_ordinal_type ;
            new_structured_type ;
            new_pointer_type .

new_ordinal_type -> enumerated_type ;
                    subrange_type .

enumerated_type -> LPAREN identifier_list RPAREN .

subrange_type -> constant DOTDOT constant .

new_structured_type -> structured_type ;
                       PACKED structured_type .

structured_type -> array_type ;
                   record_type ;
                   set_type ;
                   file_type .

array_type -> ARRAY LBRAC index_list RBRAC OF component_type .

index_list -> index_list comma index_type ;
              index_type .

index_type -> ordinal_type .

ordinal_type -> new_ordinal_type ;
                identifier .

component_type -> type_denoter .

record_type -> RECORD record_section_list END ;
               RECORD record_section_list semicolon variant_part END ;
               RECORD variant_part END .
        

record_section_list -> record_section_list semicolon record_section ;
                       record_section .

record_section -> identifier_list COLON type_denoter .

variant_part -> CASE variant_selector OF variant_list semicolon ;
                CASE variant_selector OF variant_list ;
                EMPTY .

variant_selector -> tag_field COLON tag_type ;
                    tag_type .

variant_list -> variant_list semicolon variant ;
                variant .

variant -> case_constant_list COLON LPAREN record_section_list RPAREN ;
           case_constant_list COLON LPAREN record_section_list semicolon
                variant_part RPAREN ;
           case_constant_list COLON LPAREN variant_part RPAREN .

case_constant_list -> case_constant_list comma case_constant ;
                      case_constant .

case_constant -> constant ;
                 constant DOTDOT constant .

tag_field -> identifier .

tag_type -> identifier .

set_type -> SET OF base_type .

base_type -> ordinal_type .

file_type -> tFILE OF component_type .

new_pointer_type -> UPARROW domain_type .

domain_type -> identifier .

variable_declaration_part -> VAR variable_declaration_list semicolon ;
                             EMPTY .

variable_declaration_list ->
          variable_declaration_list semicolon variable_declaration ;
          variable_declaration .

variable_declaration -> identifier_list COLON type_denoter .

procedure_and_function_declaration_part ->
                proc_or_func_declaration_list semicolon ;
                Empty .

proc_or_func_declaration_list ->
          proc_or_func_declaration_list semicolon proc_or_func_declaration ;
          proc_or_func_declaration .

proc_or_func_declaration -> procedure_declaration ;
                            function_declaration .

procedure_declaration -> procedure_heading semicolon directive ;
                         procedure_heading semicolon procedure_block .

procedure_heading -> procedure_identification ;
                     procedure_identification formal_parameter_list .

directive -> FORWARD ;
             EXTERNAL .

formal_parameter_list -> LPAREN formal_parameter_section_list RPAREN .

formal_parameter_section_list -> formal_parameter_section_list semicolon 
                                   formal_parameter_section;
                                 formal_parameter_section .

formal_parameter_section -> value_parameter_specification ;
                            variable_parameter_specification ;
                            procedural_parameter_specification ;
                            functional_parameter_specification .

value_parameter_specification -> identifier_list COLON identifier .

variable_parameter_specification -> VAR identifier_list COLON identifier .

procedural_parameter_specification -> procedure_heading .

functional_parameter_specification -> function_heading .

procedure_identification -> PROCEDURE identifier .

procedure_block -> block .

function_declaration -> function_heading semicolon directive ;
                        function_identification semicolon function_block ;
                        function_heading semicolon function_block .

function_heading -> FUNCTION identifier COLON result_type ;
                    FUNCTION identifier formal_parameter_list COLON result_type.

result_type -> identifier .

function_identification -> FUNCTION identifier .

function_block -> block .

statement_part -> compound_statement .

compound_statement -> BEGIN statement_sequence END .

statement_sequence -> statement_sequence semicolon statement ;
                      statement .

statement -> open_statement ;
             closed_statement .

open_statement -> label COLON non_labeled_open_statement ;
                  non_labeled_open_statement .

closed_statement -> label COLON non_labeled_closed_statement ;
                    non_labeled_closed_statement .

non_labeled_closed_statement -> assignment_statement ;
                                procedure_statement ;
                                goto_statement ;
                                compound_statement ;
                                case_statement ;
                                repeat_statement ;
                                closed_with_statement ;
                                closed_if_statement ;
                                closed_while_statement ;
                                closed_for_statement ;
                                Empty .

non_labeled_open_statement -> open_with_statement ;
                              open_if_statement ;
                              open_while_statement ;
                              open_for_statement .

repeat_statement -> REPEAT statement_sequence UNTIL boolean_expression .

open_while_statement -> WHILE boolean_expression DO open_statement .

closed_while_statement -> WHILE boolean_expression DO closed_statement .

open_for_statement -> FOR control_variable ASSIGNMENT initial_value direction
                        final_value DO open_statement .

closed_for_statement -> FOR control_variable ASSIGNMENT initial_value direction
                        final_value DO closed_statement .

open_with_statement -> WITH record_variable_list DO open_statement .

closed_with_statement -> WITH record_variable_list DO closed_statement .

open_if_statement -> IF boolean_expression THEN statement ;
                     IF boolean_expression 
                        THEN closed_statement ELSE open_statement .

closed_if_statement -> IF boolean_expression 
                          THEN closed_statement ELSE closed_statement .

assignment_statement -> variable_access ASSIGNMENT expression .

variable_access -> identifier ;
                   indexed_variable ;
                   field_designator ;
                   variable_access UPARROW .

indexed_variable -> variable_access LBRAC index_expression_list RBRAC .

index_expression_list -> index_expression_list comma index_expression ;
                         index_expression .

index_expression -> expression .

field_designator -> variable_access DOT identifier .

procedure_statement -> identifier params ;
                       identifier .

params -> LPAREN actual_parameter_list RPAREN .

actual_parameter_list -> actual_parameter_list comma actual_parameter ;
                         actual_parameter .

{
 * this forces you to check all this to be sure that only write and
 * writeln use the 2nd and 3rd forms, you really can't do it easily in
 * the grammar, especially since write and writeln aren't reserved
}
actual_parameter -> expression ;
                    expression COLON expression ;
                    expression COLON expression COLON expression .

goto_statement -> GOTO label .

case_statement -> CASE case_index OF case_list_element_list END ;
                  CASE case_index OF case_list_element_list SEMICOLON END ;
                  CASE case_index OF case_list_element_list semicolon
                         otherwisepart statement END ;
                  CASE case_index OF case_list_element_list semicolon
                         otherwisepart statement SEMICOLON END .

case_index -> expression .

case_list_element_list -> case_list_element_list semicolon case_list_element ;
                          case_list_element .

case_list_element -> case_constant_list COLON statement .

otherwisepart -> OTHERWISE ;
                 OTHERWISE COLON .

control_variable -> identifier .

initial_value -> expression .

direction -> TO ;
             DOWNTO .

final_value -> expression .

record_variable_list -> record_variable_list comma variable_access ;
                        variable_access .

boolean_expression -> expression .

expression -> simple_expression ;
              simple_expression relop simple_expression .

simple_expression -> term ;
                     simple_expression addop term .

term -> factor ;
        term mulop factor.

factor -> sign factor ;
          exponentiation .

exponentiation -> primary ;
                  primary STARSTAR exponentiation .

primary -> variable_access ;
           unsigned_constant ;
           function_designator ;
           set_constructor ;
           LPAREN expression RPAREN ;
           NOT primary.

unsigned_constant -> unsigned_number ;
                     CHARACTER_STRING ;
                     NIL .

unsigned_number -> unsigned_integer ; unsigned_real .

unsigned_integer -> DIGSEQ.

unsigned_real -> REALNUMBER.

{ functions with no params will be handled by plain identifier }
function_designator -> identifier params .

set_constructor -> LBRAC member_designator_list RBRAC ; 
                   LBRAC RBRAC .

member_designator_list -> member_designator_list comma member_designator ;
                          member_designator .

member_designator -> member_designator DOTDOT expression ;
                     expression .

{ Produktion gestrichen, Unterscheidung im Scanner
mulop -> STAR ;
         SLASH ;
         DIV ;
         MOD ;
         AND .
}

relop -> EQUAL ;  { = kann als Relation und als "Zuweisung" auftreten }
         tRELOP.

