program SubSequence;
const
  InputFile  = 'SEQ.INP';
  OutputFile = 'SEQ.OUT';
  max = 1000;
  maxK = 50;
var
  a: array[1..max] of Integer;
  Mark: array[1..max] of Boolean;
  B: array[0..max, 0..maxK - 1] of Byte;
  n, k, S: Integer;

procedure Enter;
var
  f: Text;
  i: Integer;
begin
  Assign(f, InputFile); Reset(f);
  Readln(f, n, k);
  S := 0;
  for i := 1 to n do
    begin
      Read(f, a[i]);
      a[i] := a[i] mod k;
      S := (S + a[i]) mod k;
    end;
  Close(f);
end;

procedure Init;
begin
  FillChar(B[0], SizeOf(B[0]), maxK + 1);
  B[0, 0] := 0;
end;

function Subtract(a, b: Integer): Integer;
begin
  a := (a - b) mod k;
  if a < 0 then Subtract := a + k
  else Subtract := a;
end;

procedure Optimize;
var
  i, t: Integer;
begin
  for i := 1 to n do
    for t := 0 to k - 1 do
      if B[i - 1, t] < B[i - 1, Subtract(t, a[i])] + 1 then
        B[i, t] := B[i - 1, t]
      else
        B[i, t] := B[i - 1, Subtract(t, a[i])] + 1;
end;

procedure Trace;
var
  i, t: Integer;
begin
  FillChar(Mark, SizeOf(Mark), True);
  t := S;
  for i := n downto 1 do
    if B[i, t] <> B[i - 1, t] then
      begin
        Mark[i] := False;
        t := Subtract(t, a[i]);
      end;
end;

procedure Result;
var
  f: Text;
  i: Integer;
begin
  Assign(f, OutputFile); Rewrite(f);
  Writeln(f, n - B[n, S]);
  for i := 1 to n do
    if Mark[i] then Write(f, i, ' ');
  Close(f);
end;

begin
  Enter;
  Init;
  Optimize;
  Trace;
  Result;
end.
