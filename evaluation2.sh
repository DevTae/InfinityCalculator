echo -e "111+222-11*3" > input1
./inf_calc input2 | grep '300' &> result_test1
if [ $? == 0 ]; then
  echo "[TEST 1] OK"
fi

echo -e "1.12+4.45-2.22*9" > input2
./inf_calc input2 | grep '-14.41' &> result_test2
if [ $? == 0 ]; then
  echo "[TEST 2] OK"
fi

echo -e "(243897+4123678)*(-347)" > input3
./inf_calc input3 | grep '-1515548525' &> result_test3
if [ $? == 0 ]; then
  echo "[TEST 3] OK"
fi

echo -e "(1.1+2.2)+(3.3-4.4)+(5.5*6.6)" > input4
./inf_calc input4 | grep '38.5' &> result_test4
if [ $? == 0 ]; then
  echo "[TEST 4] OK"
fi

echo -e "987654321.123456789+192837465.564738291*135792468.246813579" > input5
./inf_calc input5 | grep '26185900849794336.900215510800053' &> result_test5
if [ $? == 0 ]; then
  echo "[TEST 5] OK"
fi
