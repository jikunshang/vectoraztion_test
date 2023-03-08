# result

## O0 optimization
```
/workspace/lower_test \u1405 clang++  -O0 test.cpp -Rpass-analysis=loop-vectorize -Rpass=loop-vectorize -Rpass-missed=loop-vectorize -o o0.out
/workspace/lower_test \u1405 ./o0.out 
ramp up duration: 44 ms
do_lower_hint(W/ hint) duration: 24 ms
do_lower(Wo/ hint) duration: 24 ms
```

## O1 optimization
with hint, compilert can do vectorization

```
/workspace/lower_test \u1405 clang++  -O1 test.cpp -Rpass-analysis=loop-vectorize -Rpass=loop-vectorize -Rpass-missed=loop-vectorize -o o1.out
test.cpp:7:3: remark: loop not vectorized [-Rpass-missed=loop-vectorize]
  for (int i = 0; i < str_len; ++i) {
  ^
test.cpp:18:3: remark: the cost-model indicates that interleaving is not beneficial and is explicitly disabled or interleave count is set to 1 [-Rpass-analysis=loop-vectorize]
  for (int i = 0; i < str_len; ++i) {
  ^
test.cpp:18:3: remark: vectorized loop (vectorization width: 16, interleaved count: 1) [-Rpass=loop-vectorize]
test.cpp:33:3: remark: loop not vectorized [-Rpass-missed=loop-vectorize]
  for(int i=0; i< 25; i++) {
  ^
test.cpp:44:5: remark: loop not vectorized [-Rpass-missed=loop-vectorize]
    for(int i=0; i<loop_count ; i++) {
    ^
test.cpp:53:5: remark: loop not vectorized [-Rpass-missed=loop-vectorize]
    for(int i=0; i<loop_count ; i++) {
    ^
test.cpp:62:5: remark: loop not vectorized [-Rpass-missed=loop-vectorize]
    for(int i=0; i<loop_count ; i++) {
    ^
/workspace/lower_test \u1405 ./o1.out 
ramp up duration: 23 ms
do_lower_hint(W/ hint) duration: 12 ms
do_lower(Wo/ hint) duration: 11 ms

```

## O2 optimization
w/ or wo/ hints, compiler could do vectorization. Duration become 0 ms because compiler is aggresive and you do nothing meaningful.

```
/workspace/lower_test \u1405 clang++  -O2 test.cpp -Rpass-analysis=loop-vectorize -Rpass=loop-vectorize -Rpass-missed=loop-vectorize -o o2.out
test.cpp:7:3: remark: vectorized loop (vectorization width: 16, interleaved count: 2) [-Rpass=loop-vectorize]
  for (int i = 0; i < str_len; ++i) {
  ^
test.cpp:18:3: remark: vectorized loop (vectorization width: 16, interleaved count: 2) [-Rpass=loop-vectorize]
  for (int i = 0; i < str_len; ++i) {
  ^
/workspace/lower_test \u1405 ./o2.out 
ramp up duration: 0 ms
do_lower_hint(W/ hint) duration: 0 ms
do_lower(Wo/ hint) duration: 0 ms

```

## O3 optimization
same as O2
```
/workspace/lower_test \u1405 clang++  -O3 test.cpp -Rpass-analysis=loop-vectorize -Rpass=loop-vectorize -Rpass-missed=loop-vectorize -o o3.out
test.cpp:7:3: remark: vectorized loop (vectorization width: 16, interleaved count: 2) [-Rpass=loop-vectorize]
  for (int i = 0; i < str_len; ++i) {
  ^
test.cpp:18:3: remark: vectorized loop (vectorization width: 16, interleaved count: 2) [-Rpass=loop-vectorize]
  for (int i = 0; i < str_len; ++i) {
  ^
/workspace/lower_test \u1405 ./o3.out 
ramp up duration: 0 ms
do_lower_hint(W/ hint) duration: 0 ms
do_lower(Wo/ hint) duration: 0 ms

```