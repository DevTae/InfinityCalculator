echo -e "200*465+321-765*67" > input1
./inf_calc input1 | grep '42066' &> result_test1
if [ $? == 0 ]; then
  echo "[TEST 1] OK"
fi

echo -e "312.121*32.41+423*3411.4312+432.54232" > input2
./inf_calc input2 | grep '1453583.78153' &> result_test2
if [ $? == 0 ]; then
  echo "[TEST 2] OK"
fi

echo -e "421*(11-312+142*32)+(242+3*(31+42)-312)*31" > input3
./inf_calc input3 | grep '1790922' &> result_test3
if [ $? == 0 ]; then
  echo "[TEST 3] OK"
fi

echo -e "13459237578.23957278429+5832935873.23857137528-28345728345.295234523" > input4
./inf_calc input4 | grep '-9053554893.81709036343' &> result_test4
if [ $? == 0 ]; then
  echo "[TEST 4] OK"
fi

echo -e "6519851321645.984845151548+984515151455.8451552225*32215565559.663324589-20115566322.3321456622" > input5
./inf_calc input5 | grep '31716712412707382755350.353920602454016' &> result_test5
if [ $? == 0 ]; then
  echo "[TEST 5] OK"
fi

echo -e "-719-827+1000*57" > input6
./inf_calc input6 | grep '55454' &> result_test6
if [ $? == 0 ]; then
  echo "[TEST 6] OK"
fi

echo -e "-2563.2353+7547.5573-94829.3456+98978.356*32324.3434*72.466" > input7
./inf_calc input7 | grep '231848381919.5272' &> result_test7
if [ $? == 0 ]; then
  echo "[TEST 7] OK"
fi


echo -e "-53263.6543+7863.754-7432.3456*(64363.654-744.542)" > input8
./inf_calc input8 | grep '-472884627.049' &> result_test8
if [ $? == 0 ]; then
  echo "[TEST 8] OK"
fi

echo -e "65463748545425547454535.24565745635425435+2567855356454.2554765435354353*46546.4534546546554242-45345433423.3454443555474234354333" > input9
./inf_calc input9 | grep '65463868069940029504753.3570351645775129145667' &> result_test9
if [ $? == 0 ]; then
  echo "[TEST 9] OK"
fi

echo -e "100+200*300-93" > input10
./inf_calc input10 | grep '60007' &> result_test10
if [ $? == 0 ]; then
  echo "[TEST 10] OK"
fi

echo -e "23-(-34)*40+25" > input11
./inf_calc input11 | grep '1408' &> result_test11
if [ $? == 0 ]; then
  echo "[TEST 11] OK"
fi


echo -e "233423541354.143543524352+2342314123413.34523453*321341241.12341234" > input12
./inf_calc input12 | grep '752682127751965521964.9395178755481002' &> result_test12
if [ $? == 0 ]; then
  echo "[TEST 12] OK"
fi
