# Im-Select-Imm

## Introduce 
Orgin im-select could only change IME 
This version allow you change IME Mode in second parameter
The pre-build exe is under the `thisdir/out/`

## Usage 

## Get Current IME key

```shell
/path/to/im-select-imm.exe
Out: [current IME] [current Mode]
```

## Switch IME

```shell
/path/to/im-select-imm.exe [target IME]  
Or
/path/to/im-select-imm.exe [target IME]  [target IME Mode]
```

## For Microsoft Chinese IME
```
For  Microsoft Old Chinese IME(Win10 and Previous) :
    0: English
    1: Chinese
For  Microsoft New Chinese IME(Win11) :
    0: English / Half Shape
    1: Chinese / Half Shape
    1024: English / Full Shape 
    1025: Chinese / Full Shape
```