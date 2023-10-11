set -e
/.yakka/repos/yq/linux/yq e --inplace '.steps[0].input="{{build_dir}}/{{project_name}}.out"' $(pwd)/output/wiseconnect3/utilities/postbuild_profile/wiseconnect_soc.slpb
mkdir -p /gsdk/extension
ln -sf $(pwd)/output/wiseconnect3/ /gsdk/extension/wiseconnect3
/slc_cli/slc -daemon signature trust -extpath /gsdk/extension/wiseconnect3

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/crypto/attestation/attestation.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/attestation-brd4325a
make -C output/attestation-brd4325a -f attestation.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/crypto/attestation/attestation.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/attestation-brd4325c
make -C output/attestation-brd4325c -f attestation.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/crypto/attestation/attestation.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/attestation-brd4325g
make -C output/attestation-brd4325g -f attestation.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/ble/ble_accept_list/ble_accept_list.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/ble_accept_list-brd4325a
make -C output/ble_accept_list-brd4325a -f ble_accept_list.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/ble/ble_accept_list/ble_accept_list.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/ble_accept_list-brd4325c
make -C output/ble_accept_list-brd4325c -f ble_accept_list.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/ble/ble_accept_list/ble_accept_list.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/ble_accept_list-brd4325g
make -C output/ble_accept_list-brd4325g -f ble_accept_list.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/ble/ble_ae_central/ble_ae_central.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/ble_ae_central-brd4325a
make -C output/ble_ae_central-brd4325a -f ble_ae_central.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/ble/ble_ae_central/ble_ae_central.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/ble_ae_central-brd4325c
make -C output/ble_ae_central-brd4325c -f ble_ae_central.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/ble/ble_ae_central/ble_ae_central.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/ble_ae_central-brd4325g
make -C output/ble_ae_central-brd4325g -f ble_ae_central.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/ble/ble_ae_peripheral/ble_ae_peripheral.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/ble_ae_peripheral-brd4325a
make -C output/ble_ae_peripheral-brd4325a -f ble_ae_peripheral.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/ble/ble_ae_peripheral/ble_ae_peripheral.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/ble_ae_peripheral-brd4325c
make -C output/ble_ae_peripheral-brd4325c -f ble_ae_peripheral.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/ble/ble_ae_peripheral/ble_ae_peripheral.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/ble_ae_peripheral-brd4325g
make -C output/ble_ae_peripheral-brd4325g -f ble_ae_peripheral.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/ble/ble_central/ble_central_ncp.slcp --force --with "brd4180b" -np -d output/ble_central_ncp-brd4180b
make -C output/ble_central_ncp-brd4180b -f ble_central_ncp.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/ble/ble_central/ble_central_soc.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/ble_central_soc-brd4325a
make -C output/ble_central_soc-brd4325a -f ble_central_soc.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/ble/ble_central/ble_central_soc.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/ble_central_soc-brd4325c
make -C output/ble_central_soc-brd4325c -f ble_central_soc.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/ble/ble_central/ble_central_soc.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/ble_central_soc-brd4325g
make -C output/ble_central_soc-brd4325g -f ble_central_soc.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/ble/ble_datalength/ble_datalength.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/ble_datalength-brd4325a
make -C output/ble_datalength-brd4325a -f ble_datalength.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/ble/ble_datalength/ble_datalength.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/ble_datalength-brd4325c
make -C output/ble_datalength-brd4325c -f ble_datalength.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/ble/ble_datalength/ble_datalength.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/ble_datalength-brd4325g
make -C output/ble_datalength-brd4325g -f ble_datalength.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/ble/gatt_long_read/gatt_long_read.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/ble_gatt_long_read-brd4325a
make -C output/ble_gatt_long_read-brd4325a -f ble_gatt_long_read.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/ble/gatt_long_read/gatt_long_read.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/ble_gatt_long_read-brd4325c
make -C output/ble_gatt_long_read-brd4325c -f ble_gatt_long_read.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/ble/gatt_long_read/gatt_long_read.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/ble_gatt_long_read-brd4325g
make -C output/ble_gatt_long_read-brd4325g -f ble_gatt_long_read.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/ble/ble_heart_rate_profile/ble_heart_rate_profile_ncp.slcp --force --with "brd4180b" -np -d output/ble_heart_rate_profile_ncp-brd4180b
make -C output/ble_heart_rate_profile_ncp-brd4180b -f ble_heart_rate_profile_ncp.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/ble/ble_heart_rate_profile/ble_heart_rate_profile_soc.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/ble_heart_rate_profile_soc-brd4325a
make -C output/ble_heart_rate_profile_soc-brd4325a -f ble_heart_rate_profile_soc.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/ble/ble_heart_rate_profile/ble_heart_rate_profile_soc.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/ble_heart_rate_profile_soc-brd4325c
make -C output/ble_heart_rate_profile_soc-brd4325c -f ble_heart_rate_profile_soc.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/ble/ble_heart_rate_profile/ble_heart_rate_profile_soc.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/ble_heart_rate_profile_soc-brd4325g
make -C output/ble_heart_rate_profile_soc-brd4325g -f ble_heart_rate_profile_soc.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/ble/ble_hid_on_gatt/ble_hid_on_gatt.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/ble_hid_on_gatt-brd4325a
make -C output/ble_hid_on_gatt-brd4325a -f ble_hid_on_gatt.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/ble/ble_hid_on_gatt/ble_hid_on_gatt.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/ble_hid_on_gatt-brd4325c
make -C output/ble_hid_on_gatt-brd4325c -f ble_hid_on_gatt.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/ble/ble_hid_on_gatt/ble_hid_on_gatt.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/ble_hid_on_gatt-brd4325g
make -C output/ble_hid_on_gatt-brd4325g -f ble_hid_on_gatt.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/ble/ble_ibeacon/ble_ibeacon_ncp.slcp --force --with "brd4180b" -np -d output/ble_ibeacon_ncp-brd4180b
make -C output/ble_ibeacon_ncp-brd4180b -f ble_ibeacon_ncp.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/ble/ble_ibeacon/ble_ibeacon_soc.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/ble_ibeacon_soc-brd4325a
make -C output/ble_ibeacon_soc-brd4325a -f ble_ibeacon_soc.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/ble/ble_ibeacon/ble_ibeacon_soc.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/ble_ibeacon_soc-brd4325c
make -C output/ble_ibeacon_soc-brd4325c -f ble_ibeacon_soc.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/ble/ble_ibeacon/ble_ibeacon_soc.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/ble_ibeacon_soc-brd4325g
make -C output/ble_ibeacon_soc-brd4325g -f ble_ibeacon_soc.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/ble/ble_longrange_2mbps/ble_longrange_2mbps.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/ble_longrange_2mbps-brd4325a
make -C output/ble_longrange_2mbps-brd4325a -f ble_longrange_2mbps.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/ble/ble_longrange_2mbps/ble_longrange_2mbps.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/ble_longrange_2mbps-brd4325c
make -C output/ble_longrange_2mbps-brd4325c -f ble_longrange_2mbps.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/ble/ble_longrange_2mbps/ble_longrange_2mbps.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/ble_longrange_2mbps-brd4325g
make -C output/ble_longrange_2mbps-brd4325g -f ble_longrange_2mbps.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/ble/ble_multiconnection_gatt_test/ble_multiconnection_gatt_test.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/ble_multiconnection_gatt_test-brd4325a
make -C output/ble_multiconnection_gatt_test-brd4325a -f ble_multiconnection_gatt_test.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/ble/ble_multiconnection_gatt_test/ble_multiconnection_gatt_test.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/ble_multiconnection_gatt_test-brd4325c
make -C output/ble_multiconnection_gatt_test-brd4325c -f ble_multiconnection_gatt_test.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/ble/ble_multiconnection_gatt_test/ble_multiconnection_gatt_test.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/ble_multiconnection_gatt_test-brd4325g
make -C output/ble_multiconnection_gatt_test-brd4325g -f ble_multiconnection_gatt_test.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/featured/ble_per/ble_per_ncp.slcp --force --with "brd4180b" -np -d output/ble_per_ncp-brd4180b
make -C output/ble_per_ncp-brd4180b -f ble_per_ncp.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/featured/ble_per/ble_per_soc.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/ble_per_soc-brd4325a
make -C output/ble_per_soc-brd4325a -f ble_per_soc.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/featured/ble_per/ble_per_soc.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/ble_per_soc-brd4325c
make -C output/ble_per_soc-brd4325c -f ble_per_soc.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/featured/ble_per/ble_per_soc.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/ble_per_soc-brd4325g
make -C output/ble_per_soc-brd4325g -f ble_per_soc.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/ble/ble_power_save/ble_power_save_ncp.slcp --force --with "brd4180b" -np -d output/ble_power_save_ncp-brd4180b
make -C output/ble_power_save_ncp-brd4180b -f ble_power_save_ncp.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/ble/ble_power_save/ble_power_save_soc.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/ble_power_save_soc-brd4325a
make -C output/ble_power_save_soc-brd4325a -f ble_power_save_soc.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/ble/ble_power_save/ble_power_save_soc.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/ble_power_save_soc-brd4325c
make -C output/ble_power_save_soc-brd4325c -f ble_power_save_soc.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/ble/ble_power_save/ble_power_save_soc.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/ble_power_save_soc-brd4325g
make -C output/ble_power_save_soc-brd4325g -f ble_power_save_soc.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/ble/ble_privacy/ble_privacy_ncp.slcp --force --with "brd4180b" -np -d output/ble_privacy_ncp-brd4180b
make -C output/ble_privacy_ncp-brd4180b -f ble_privacy_ncp.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/ble/ble_privacy/ble_privacy_soc.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/ble_privacy_soc-brd4325a
make -C output/ble_privacy_soc-brd4325a -f ble_privacy_soc.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/ble/ble_privacy/ble_privacy_soc.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/ble_privacy_soc-brd4325c
make -C output/ble_privacy_soc-brd4325c -f ble_privacy_soc.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/ble/ble_privacy/ble_privacy_soc.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/ble_privacy_soc-brd4325g
make -C output/ble_privacy_soc-brd4325g -f ble_privacy_soc.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/ble/ble_secureconnection/ble_secureconnection_ncp.slcp --force --with "brd4180b" -np -d output/ble_secureconnection_ncp-brd4180b
make -C output/ble_secureconnection_ncp-brd4180b -f ble_secureconnection_ncp.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/ble/ble_secureconnection/ble_secureconnection_soc.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/ble_secureconnection_soc-brd4325a
make -C output/ble_secureconnection_soc-brd4325a -f ble_secureconnection_soc.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/ble/ble_secureconnection/ble_secureconnection_soc.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/ble_secureconnection_soc-brd4325c
make -C output/ble_secureconnection_soc-brd4325c -f ble_secureconnection_soc.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/ble/ble_secureconnection/ble_secureconnection_soc.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/ble_secureconnection_soc-brd4325g
make -C output/ble_secureconnection_soc-brd4325g -f ble_secureconnection_soc.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/ble/ble_testmodes/ble_testmodes_ncp.slcp --force --with "brd4180b" -np -d output/ble_testmodes_ncp-brd4180b
make -C output/ble_testmodes_ncp-brd4180b -f ble_testmodes_ncp.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/ble/ble_testmodes/ble_testmodes_soc.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/ble_testmodes_soc-brd4325a
make -C output/ble_testmodes_soc-brd4325a -f ble_testmodes_soc.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/ble/ble_testmodes/ble_testmodes_soc.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/ble_testmodes_soc-brd4325c
make -C output/ble_testmodes_soc-brd4325c -f ble_testmodes_soc.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/ble/ble_testmodes/ble_testmodes_soc.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/ble_testmodes_soc-brd4325g
make -C output/ble_testmodes_soc-brd4325g -f ble_testmodes_soc.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/ble/ble_throughput_app/ble_throughput_app_ncp.slcp --force --with "brd4180b" -np -d output/ble_throughput_app_ncp-brd4180b
make -C output/ble_throughput_app_ncp-brd4180b -f ble_throughput_app_ncp.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/ble/ble_throughput_app/ble_throughput_app_soc.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/ble_throughput_app_soc-brd4325a
make -C output/ble_throughput_app_soc-brd4325a -f ble_throughput_app_soc.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/ble/ble_throughput_app/ble_throughput_app_soc.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/ble_throughput_app_soc-brd4325c
make -C output/ble_throughput_app_soc-brd4325c -f ble_throughput_app_soc.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/ble/ble_throughput_app/ble_throughput_app_soc.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/ble_throughput_app_soc-brd4325g
make -C output/ble_throughput_app_soc-brd4325g -f ble_throughput_app_soc.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/cli_demo/cli_demo.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/cli_demo-brd4325a
make -C output/cli_demo-brd4325a -f cli_demo.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/cli_demo/cli_demo.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/cli_demo-brd4325c
make -C output/cli_demo-brd4325c -f cli_demo.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/cli_demo/cli_demo.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/cli_demo-brd4325g
make -C output/cli_demo-brd4325g -f cli_demo.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/crypto/aes/aes.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/crypto_aes-brd4325a
make -C output/crypto_aes-brd4325a -f crypto_aes.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/crypto/aes/aes.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/crypto_aes-brd4325c
make -C output/crypto_aes-brd4325c -f crypto_aes.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/crypto/aes/aes.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/crypto_aes-brd4325g
make -C output/crypto_aes-brd4325g -f crypto_aes.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/crypto/ecdh/ecdh.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/crypto_ecdh-brd4325a
make -C output/crypto_ecdh-brd4325a -f crypto_ecdh.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/crypto/ecdh/ecdh.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/crypto_ecdh-brd4325c
make -C output/crypto_ecdh-brd4325c -f crypto_ecdh.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/crypto/ecdh/ecdh.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/crypto_ecdh-brd4325g
make -C output/crypto_ecdh-brd4325g -f crypto_ecdh.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/crypto/hmac/hmac.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/crypto_hmac-brd4325a
make -C output/crypto_hmac-brd4325a -f crypto_hmac.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/crypto/hmac/hmac.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/crypto_hmac-brd4325c
make -C output/crypto_hmac-brd4325c -f crypto_hmac.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/crypto/hmac/hmac.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/crypto_hmac-brd4325g
make -C output/crypto_hmac-brd4325g -f crypto_hmac.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/crypto/sha/sha.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/crypto_sha-brd4325a
make -C output/crypto_sha-brd4325a -f crypto_sha.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/crypto/sha/sha.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/crypto_sha-brd4325c
make -C output/crypto_sha-brd4325c -f crypto_sha.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/crypto/sha/sha.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/crypto_sha-brd4325g
make -C output/crypto_sha-brd4325g -f crypto_sha.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/iostream_usart_baremetal/iostream_usart_baremetal.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/iostream_usart_baremetal-brd4325a
make -C output/iostream_usart_baremetal-brd4325a -f iostream_usart_baremetal.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/iostream_usart_baremetal/iostream_usart_baremetal.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/iostream_usart_baremetal-brd4325c
make -C output/iostream_usart_baremetal-brd4325c -f iostream_usart_baremetal.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/iostream_usart_baremetal/iostream_usart_baremetal.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/iostream_usart_baremetal-brd4325g
make -C output/iostream_usart_baremetal-brd4325g -f iostream_usart_baremetal.Makefile -j$((`nproc`/4))


/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/psram_blinky/psram_blinky.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/psram_blinky-brd4325g
make -C output/psram_blinky-brd4325g -f psram_blinky.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/psram_driver_example/psram_driver_example.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/psram_driver_example-brd4325g
make -C output/psram_driver_example-brd4325g -f psram_driver_example.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/crypto/si91x_psa_aes/si91x_psa_aes.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/si91x_psa_aes-brd4325a
make -C output/si91x_psa_aes-brd4325a -f si91x_psa_aes.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/crypto/si91x_psa_aes/si91x_psa_aes.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/si91x_psa_aes-brd4325c
make -C output/si91x_psa_aes-brd4325c -f si91x_psa_aes.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/crypto/si91x_psa_aes/si91x_psa_aes.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/si91x_psa_aes-brd4325g
make -C output/si91x_psa_aes-brd4325g -f si91x_psa_aes.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/crypto/si91x_psa_asymmetric_key_storage/si91x_psa_asymmetric_key_storage.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/si91x_psa_asymmetric_key_storage-brd4325a
make -C output/si91x_psa_asymmetric_key_storage-brd4325a -f si91x_psa_asymmetric_key_storage.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/crypto/si91x_psa_asymmetric_key_storage/si91x_psa_asymmetric_key_storage.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/si91x_psa_asymmetric_key_storage-brd4325c
make -C output/si91x_psa_asymmetric_key_storage-brd4325c -f si91x_psa_asymmetric_key_storage.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/crypto/si91x_psa_asymmetric_key_storage/si91x_psa_asymmetric_key_storage.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/si91x_psa_asymmetric_key_storage-brd4325g
make -C output/si91x_psa_asymmetric_key_storage-brd4325g -f si91x_psa_asymmetric_key_storage.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/crypto/si91x_psa_ccm/si91x_psa_ccm.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/si91x_psa_ccm-brd4325a
make -C output/si91x_psa_ccm-brd4325a -f si91x_psa_ccm.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/crypto/si91x_psa_ccm/si91x_psa_ccm.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/si91x_psa_ccm-brd4325c
make -C output/si91x_psa_ccm-brd4325c -f si91x_psa_ccm.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/crypto/si91x_psa_ccm/si91x_psa_ccm.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/si91x_psa_ccm-brd4325g
make -C output/si91x_psa_ccm-brd4325g -f si91x_psa_ccm.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/crypto/si91x_psa_chachapoly/si91x_psa_chachapoly.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/si91x_psa_chachapoly-brd4325a
make -C output/si91x_psa_chachapoly-brd4325a -f si91x_psa_chachapoly.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/crypto/si91x_psa_chachapoly/si91x_psa_chachapoly.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/si91x_psa_chachapoly-brd4325c
make -C output/si91x_psa_chachapoly-brd4325c -f si91x_psa_chachapoly.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/crypto/si91x_psa_chachapoly/si91x_psa_chachapoly.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/si91x_psa_chachapoly-brd4325g
make -C output/si91x_psa_chachapoly-brd4325g -f si91x_psa_chachapoly.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/crypto/si91x_psa_ecdh/si91x_psa_ecdh.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/si91x_psa_ecdh-brd4325a
make -C output/si91x_psa_ecdh-brd4325a -f si91x_psa_ecdh.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/crypto/si91x_psa_ecdh/si91x_psa_ecdh.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/si91x_psa_ecdh-brd4325c
make -C output/si91x_psa_ecdh-brd4325c -f si91x_psa_ecdh.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/crypto/si91x_psa_ecdh/si91x_psa_ecdh.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/si91x_psa_ecdh-brd4325g
make -C output/si91x_psa_ecdh-brd4325g -f si91x_psa_ecdh.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/crypto/si91x_psa_gcm/si91x_psa_gcm.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/si91x_psa_gcm-brd4325a
make -C output/si91x_psa_gcm-brd4325a -f si91x_psa_gcm.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/crypto/si91x_psa_gcm/si91x_psa_gcm.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/si91x_psa_gcm-brd4325c
make -C output/si91x_psa_gcm-brd4325c -f si91x_psa_gcm.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/crypto/si91x_psa_gcm/si91x_psa_gcm.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/si91x_psa_gcm-brd4325g
make -C output/si91x_psa_gcm-brd4325g -f si91x_psa_gcm.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/crypto/si91x_psa_hmac/si91x_psa_hmac.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/si91x_psa_hmac-brd4325a
make -C output/si91x_psa_hmac-brd4325a -f si91x_psa_hmac.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/crypto/si91x_psa_hmac/si91x_psa_hmac.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/si91x_psa_hmac-brd4325c
make -C output/si91x_psa_hmac-brd4325c -f si91x_psa_hmac.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/crypto/si91x_psa_hmac/si91x_psa_hmac.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/si91x_psa_hmac-brd4325g
make -C output/si91x_psa_hmac-brd4325g -f si91x_psa_hmac.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/crypto/si91x_psa_sha/si91x_psa_sha.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/si91x_psa_sha-brd4325a
make -C output/si91x_psa_sha-brd4325a -f si91x_psa_sha.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/crypto/si91x_psa_sha/si91x_psa_sha.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/si91x_psa_sha-brd4325c
make -C output/si91x_psa_sha-brd4325c -f si91x_psa_sha.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/crypto/si91x_psa_sha/si91x_psa_sha.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/si91x_psa_sha-brd4325g
make -C output/si91x_psa_sha-brd4325g -f si91x_psa_sha.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/crypto/si91x_psa_symmetric_key_storage/si91x_psa_symmetric_key_storage.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/si91x_psa_symmetric_key_storage-brd4325a
make -C output/si91x_psa_symmetric_key_storage-brd4325a -f si91x_psa_symmetric_key_storage.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/crypto/si91x_psa_symmetric_key_storage/si91x_psa_symmetric_key_storage.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/si91x_psa_symmetric_key_storage-brd4325c
make -C output/si91x_psa_symmetric_key_storage-brd4325c -f si91x_psa_symmetric_key_storage.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/crypto/si91x_psa_symmetric_key_storage/si91x_psa_symmetric_key_storage.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/si91x_psa_symmetric_key_storage-brd4325g
make -C output/si91x_psa_symmetric_key_storage-brd4325g -f si91x_psa_symmetric_key_storage.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_adc/sl_si91x_adc.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/sl_si91x_adc-brd4325a
make -C output/sl_si91x_adc-brd4325a -f sl_si91x_adc.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_adc/sl_si91x_adc.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/sl_si91x_adc-brd4325c
make -C output/sl_si91x_adc-brd4325c -f sl_si91x_adc.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_adc/sl_si91x_adc.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/sl_si91x_adc-brd4325g
make -C output/sl_si91x_adc-brd4325g -f sl_si91x_adc.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_blinky/sl_si91x_blinky.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/sl_si91x_blinky-brd4325a
make -C output/sl_si91x_blinky-brd4325a -f sl_si91x_blinky.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_blinky/sl_si91x_blinky.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/sl_si91x_blinky-brd4325c
make -C output/sl_si91x_blinky-brd4325c -f sl_si91x_blinky.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_blinky/sl_si91x_blinky.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/sl_si91x_blinky-brd4325g
make -C output/sl_si91x_blinky-brd4325g -f sl_si91x_blinky.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_button_baremetal/sl_si91x_button_baremetal.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/sl_si91x_button_baremetal-brd4325a
make -C output/sl_si91x_button_baremetal-brd4325a -f sl_si91x_button_baremetal.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_button_baremetal/sl_si91x_button_baremetal.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/sl_si91x_button_baremetal-brd4325c
make -C output/sl_si91x_button_baremetal-brd4325c -f sl_si91x_button_baremetal.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_button_baremetal/sl_si91x_button_baremetal.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/sl_si91x_button_baremetal-brd4325g
make -C output/sl_si91x_button_baremetal-brd4325g -f sl_si91x_button_baremetal.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_calendar/sl_si91x_calendar.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/sl_si91x_calendar-brd4325a
make -C output/sl_si91x_calendar-brd4325a -f sl_si91x_calendar.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_calendar/sl_si91x_calendar.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/sl_si91x_calendar-brd4325c
make -C output/sl_si91x_calendar-brd4325c -f sl_si91x_calendar.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_calendar/sl_si91x_calendar.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/sl_si91x_calendar-brd4325g
make -C output/sl_si91x_calendar-brd4325g -f sl_si91x_calendar.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_config_timer/sl_si91x_config_timer.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/sl_si91x_config_timer-brd4325a
make -C output/sl_si91x_config_timer-brd4325a -f sl_si91x_config_timer.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_config_timer/sl_si91x_config_timer.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/sl_si91x_config_timer-brd4325c
make -C output/sl_si91x_config_timer-brd4325c -f sl_si91x_config_timer.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_config_timer/sl_si91x_config_timer.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/sl_si91x_config_timer-brd4325g
make -C output/sl_si91x_config_timer-brd4325g -f sl_si91x_config_timer.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_dma/sl_si91x_dma.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/sl_si91x_dma-brd4325a
make -C output/sl_si91x_dma-brd4325a -f sl_si91x_dma.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_dma/sl_si91x_dma.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/sl_si91x_dma-brd4325c
make -C output/sl_si91x_dma-brd4325c -f sl_si91x_dma.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_dma/sl_si91x_dma.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/sl_si91x_dma-brd4325g
make -C output/sl_si91x_dma-brd4325g -f sl_si91x_dma.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_driver_gpio/sl_si91x_driver_gpio.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/sl_si91x_driver_gpio-brd4325a
make -C output/sl_si91x_driver_gpio-brd4325a -f sl_si91x_driver_gpio.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_driver_gpio/sl_si91x_driver_gpio.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/sl_si91x_driver_gpio-brd4325c
make -C output/sl_si91x_driver_gpio-brd4325c -f sl_si91x_driver_gpio.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_driver_gpio/sl_si91x_driver_gpio.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/sl_si91x_driver_gpio-brd4325g
make -C output/sl_si91x_driver_gpio-brd4325g -f sl_si91x_driver_gpio.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_efuse/sl_si91x_efuse.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/sl_si91x_efuse-brd4325a
make -C output/sl_si91x_efuse-brd4325a -f sl_si91x_efuse.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_efuse/sl_si91x_efuse.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/sl_si91x_efuse-brd4325c
make -C output/sl_si91x_efuse-brd4325c -f sl_si91x_efuse.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_efuse/sl_si91x_efuse.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/sl_si91x_efuse-brd4325g
make -C output/sl_si91x_efuse-brd4325g -f sl_si91x_efuse.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_gpio/sl_si91x_gpio.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/sl_si91x_gpio-brd4325a
make -C output/sl_si91x_gpio-brd4325a -f sl_si91x_gpio.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_gpio/sl_si91x_gpio.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/sl_si91x_gpio-brd4325c
make -C output/sl_si91x_gpio-brd4325c -f sl_si91x_gpio.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_gpio/sl_si91x_gpio.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/sl_si91x_gpio-brd4325g
make -C output/sl_si91x_gpio-brd4325g -f sl_si91x_gpio.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_gspi/sl_si91x_gspi.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/sl_si91x_gspi-brd4325a
make -C output/sl_si91x_gspi-brd4325a -f sl_si91x_gspi.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_gspi/sl_si91x_gspi.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/sl_si91x_gspi-brd4325c
make -C output/sl_si91x_gspi-brd4325c -f sl_si91x_gspi.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_gspi/sl_si91x_gspi.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/sl_si91x_gspi-brd4325g
make -C output/sl_si91x_gspi-brd4325g -f sl_si91x_gspi.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_i2c_follower/sl_si91x_i2c_follower.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/sl_si91x_i2c_follower-brd4325a
make -C output/sl_si91x_i2c_follower-brd4325a -f sl_si91x_i2c_follower.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_i2c_follower/sl_si91x_i2c_follower.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/sl_si91x_i2c_follower-brd4325c
make -C output/sl_si91x_i2c_follower-brd4325c -f sl_si91x_i2c_follower.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_i2c_follower/sl_si91x_i2c_follower.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/sl_si91x_i2c_follower-brd4325g
make -C output/sl_si91x_i2c_follower-brd4325g -f sl_si91x_i2c_follower.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_i2c_leader/sl_si91x_i2c_leader.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/sl_si91x_i2c_leader-brd4325a
make -C output/sl_si91x_i2c_leader-brd4325a -f sl_si91x_i2c_leader.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_i2c_leader/sl_si91x_i2c_leader.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/sl_si91x_i2c_leader-brd4325c
make -C output/sl_si91x_i2c_leader-brd4325c -f sl_si91x_i2c_leader.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_i2c_leader/sl_si91x_i2c_leader.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/sl_si91x_i2c_leader-brd4325g
make -C output/sl_si91x_i2c_leader-brd4325g -f sl_si91x_i2c_leader.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_i2s_loopback/sl_si91x_i2s_loopback.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/sl_si91x_i2s_loopback-brd4325a
make -C output/sl_si91x_i2s_loopback-brd4325a -f sl_si91x_i2s_loopback.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_i2s_loopback/sl_si91x_i2s_loopback.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/sl_si91x_i2s_loopback-brd4325c
make -C output/sl_si91x_i2s_loopback-brd4325c -f sl_si91x_i2s_loopback.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_i2s_loopback/sl_si91x_i2s_loopback.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/sl_si91x_i2s_loopback-brd4325g
make -C output/sl_si91x_i2s_loopback-brd4325g -f sl_si91x_i2s_loopback.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_i2s_low_power/sl_si91x_i2s_low_power.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/sl_si91x_i2s_low_power-brd4325a
make -C output/sl_si91x_i2s_low_power-brd4325a -f sl_si91x_i2s_low_power.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_i2s_low_power/sl_si91x_i2s_low_power.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/sl_si91x_i2s_low_power-brd4325c
make -C output/sl_si91x_i2s_low_power-brd4325c -f sl_si91x_i2s_low_power.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_i2s_low_power/sl_si91x_i2s_low_power.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/sl_si91x_i2s_low_power-brd4325g
make -C output/sl_si91x_i2s_low_power-brd4325g -f sl_si91x_i2s_low_power.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_i2s_primary/sl_si91x_i2s_primary.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/sl_si91x_i2s_primary-brd4325a
make -C output/sl_si91x_i2s_primary-brd4325a -f sl_si91x_i2s_primary.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_i2s_primary/sl_si91x_i2s_primary.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/sl_si91x_i2s_primary-brd4325c
make -C output/sl_si91x_i2s_primary-brd4325c -f sl_si91x_i2s_primary.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_i2s_primary/sl_si91x_i2s_primary.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/sl_si91x_i2s_primary-brd4325g
make -C output/sl_si91x_i2s_primary-brd4325g -f sl_si91x_i2s_primary.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_i2s_secondary/sl_si91x_i2s_secondary.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/sl_si91x_i2s_secondary-brd4325a
make -C output/sl_si91x_i2s_secondary-brd4325a -f sl_si91x_i2s_secondary.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_i2s_secondary/sl_si91x_i2s_secondary.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/sl_si91x_i2s_secondary-brd4325c
make -C output/sl_si91x_i2s_secondary-brd4325c -f sl_si91x_i2s_secondary.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_i2s_secondary/sl_si91x_i2s_secondary.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/sl_si91x_i2s_secondary-brd4325g
make -C output/sl_si91x_i2s_secondary-brd4325g -f sl_si91x_i2s_secondary.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_ml_model_profiler/sl_si91x_ml_model_profiler.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/sl_si91x_ml_model_profiler-brd4325c
make -C output/sl_si91x_ml_model_profiler-brd4325c -f sl_si91x_ml_model_profiler.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_ml_model_profiler/sl_si91x_ml_model_profiler.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/sl_si91x_ml_model_profiler-brd4325g
make -C output/sl_si91x_ml_model_profiler-brd4325g -f sl_si91x_ml_model_profiler.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/service/sl_si91x_nvm3_common_flash/sl_si91x_nvm3_common_flash.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/sl_si91x_nvm3_common_flash-brd4325a
make -C output/sl_si91x_nvm3_common_flash-brd4325a -f sl_si91x_nvm3_common_flash.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/service/sl_si91x_nvm3_common_flash/sl_si91x_nvm3_common_flash.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/sl_si91x_nvm3_common_flash-brd4325c
make -C output/sl_si91x_nvm3_common_flash-brd4325c -f sl_si91x_nvm3_common_flash.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/service/sl_si91x_nvm3_common_flash/sl_si91x_nvm3_common_flash.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/sl_si91x_nvm3_common_flash-brd4325g
make -C output/sl_si91x_nvm3_common_flash-brd4325g -f sl_si91x_nvm3_common_flash.Makefile -j$((`nproc`/4))


/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_pwm/sl_si91x_pwm.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/sl_si91x_pwm-brd4325c
make -C output/sl_si91x_pwm-brd4325c -f sl_si91x_pwm.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_pwm/sl_si91x_pwm.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/sl_si91x_pwm-brd4325g
make -C output/sl_si91x_pwm-brd4325g -f sl_si91x_pwm.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_sdio_secondary/sl_si91x_sdio_secondary.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/sl_si91x_sdio_secondary-brd4325a
make -C output/sl_si91x_sdio_secondary-brd4325a -f sl_si91x_sdio_secondary.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_sensorhub/sl_si91x_sensorhub.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/sl_si91x_sensorhub-brd4325a
make -C output/sl_si91x_sensorhub-brd4325a -f sl_si91x_sensorhub.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_sensorhub/sl_si91x_sensorhub.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/sl_si91x_sensorhub-brd4325c
make -C output/sl_si91x_sensorhub-brd4325c -f sl_si91x_sensorhub.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_sensorhub/sl_si91x_sensorhub.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/sl_si91x_sensorhub-brd4325g
make -C output/sl_si91x_sensorhub-brd4325g -f sl_si91x_sensorhub.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_sio/sl_si91x_sio.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/sl_si91x_sio-brd4325c
make -C output/sl_si91x_sio-brd4325c -f sl_si91x_sio.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_sio/sl_si91x_sio.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/sl_si91x_sio-brd4325g
make -C output/sl_si91x_sio-brd4325g -f sl_si91x_sio.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/service/sl_si91x_sleeptimer/sl_si91x_sleeptimer.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/sl_si91x_sleeptimer-brd4325c
make -C output/sl_si91x_sleeptimer-brd4325c -f sl_si91x_sleeptimer.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/service/sl_si91x_sleeptimer/sl_si91x_sleeptimer.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/sl_si91x_sleeptimer-brd4325g
make -C output/sl_si91x_sleeptimer-brd4325g -f sl_si91x_sleeptimer.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_ssi_master/sl_si91x_ssi_master.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/sl_si91x_ssi_master-brd4325a
make -C output/sl_si91x_ssi_master-brd4325a -f sl_si91x_ssi_master.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_ssi_master/sl_si91x_ssi_master.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/sl_si91x_ssi_master-brd4325c
make -C output/sl_si91x_ssi_master-brd4325c -f sl_si91x_ssi_master.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_ssi_master/sl_si91x_ssi_master.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/sl_si91x_ssi_master-brd4325g
make -C output/sl_si91x_ssi_master-brd4325g -f sl_si91x_ssi_master.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_ssi_slave/sl_si91x_ssi_slave.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/sl_si91x_ssi_slave-brd4325a
make -C output/sl_si91x_ssi_slave-brd4325a -f sl_si91x_ssi_slave.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_ssi_slave/sl_si91x_ssi_slave.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/sl_si91x_ssi_slave-brd4325c
make -C output/sl_si91x_ssi_slave-brd4325c -f sl_si91x_ssi_slave.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_ssi_slave/sl_si91x_ssi_slave.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/sl_si91x_ssi_slave-brd4325g
make -C output/sl_si91x_ssi_slave-brd4325g -f sl_si91x_ssi_slave.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_sysrtc/sl_si91x_sysrtc.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/sl_si91x_sysrtc-brd4325c
make -C output/sl_si91x_sysrtc-brd4325c -f sl_si91x_sysrtc.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_sysrtc/sl_si91x_sysrtc.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/sl_si91x_sysrtc-brd4325g
make -C output/sl_si91x_sysrtc-brd4325g -f sl_si91x_sysrtc.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_ulp_adc/sl_si91x_ulp_adc.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/sl_si91x_ulp_adc-brd4325a
make -C output/sl_si91x_ulp_adc-brd4325a -f sl_si91x_ulp_adc.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_ulp_adc/sl_si91x_ulp_adc.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/sl_si91x_ulp_adc-brd4325c
make -C output/sl_si91x_ulp_adc-brd4325c -f sl_si91x_ulp_adc.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_ulp_adc/sl_si91x_ulp_adc.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/sl_si91x_ulp_adc-brd4325g
make -C output/sl_si91x_ulp_adc-brd4325g -f sl_si91x_ulp_adc.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_ulp_calendar/sl_si91x_ulp_calendar.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/sl_si91x_ulp_calendar-brd4325a
make -C output/sl_si91x_ulp_calendar-brd4325a -f sl_si91x_ulp_calendar.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_ulp_calendar/sl_si91x_ulp_calendar.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/sl_si91x_ulp_calendar-brd4325c
make -C output/sl_si91x_ulp_calendar-brd4325c -f sl_si91x_ulp_calendar.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_ulp_calendar/sl_si91x_ulp_calendar.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/sl_si91x_ulp_calendar-brd4325g
make -C output/sl_si91x_ulp_calendar-brd4325g -f sl_si91x_ulp_calendar.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_ulp_dma/sl_si91x_ulp_dma.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/sl_si91x_ulp_dma-brd4325a
make -C output/sl_si91x_ulp_dma-brd4325a -f sl_si91x_ulp_dma.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_ulp_dma/sl_si91x_ulp_dma.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/sl_si91x_ulp_dma-brd4325c
make -C output/sl_si91x_ulp_dma-brd4325c -f sl_si91x_ulp_dma.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_ulp_dma/sl_si91x_ulp_dma.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/sl_si91x_ulp_dma-brd4325g
make -C output/sl_si91x_ulp_dma-brd4325g -f sl_si91x_ulp_dma.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_ulp_gpio/sl_si91x_ulp_gpio.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/sl_si91x_ulp_gpio-brd4325a
make -C output/sl_si91x_ulp_gpio-brd4325a -f sl_si91x_ulp_gpio.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_ulp_gpio/sl_si91x_ulp_gpio.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/sl_si91x_ulp_gpio-brd4325c
make -C output/sl_si91x_ulp_gpio-brd4325c -f sl_si91x_ulp_gpio.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_ulp_gpio/sl_si91x_ulp_gpio.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/sl_si91x_ulp_gpio-brd4325g
make -C output/sl_si91x_ulp_gpio-brd4325g -f sl_si91x_ulp_gpio.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_ulp_i2c_leader/sl_si91x_ulp_i2c_leader.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/sl_si91x_ulp_i2c_leader-brd4325a
make -C output/sl_si91x_ulp_i2c_leader-brd4325a -f sl_si91x_ulp_i2c_leader.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_ulp_i2c_leader/sl_si91x_ulp_i2c_leader.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/sl_si91x_ulp_i2c_leader-brd4325c
make -C output/sl_si91x_ulp_i2c_leader-brd4325c -f sl_si91x_ulp_i2c_leader.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_ulp_i2c_leader/sl_si91x_ulp_i2c_leader.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/sl_si91x_ulp_i2c_leader-brd4325g
make -C output/sl_si91x_ulp_i2c_leader-brd4325g -f sl_si91x_ulp_i2c_leader.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_ulp_ssi_master/sl_si91x_ulp_ssi_master.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/sl_si91x_ulp_ssi_master-brd4325a
make -C output/sl_si91x_ulp_ssi_master-brd4325a -f sl_si91x_ulp_ssi_master.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_ulp_ssi_master/sl_si91x_ulp_ssi_master.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/sl_si91x_ulp_ssi_master-brd4325c
make -C output/sl_si91x_ulp_ssi_master-brd4325c -f sl_si91x_ulp_ssi_master.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_ulp_ssi_master/sl_si91x_ulp_ssi_master.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/sl_si91x_ulp_ssi_master-brd4325g
make -C output/sl_si91x_ulp_ssi_master-brd4325g -f sl_si91x_ulp_ssi_master.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_ulp_timer/sl_si91x_ulp_timer.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/sl_si91x_ulp_timer-brd4325a
make -C output/sl_si91x_ulp_timer-brd4325a -f sl_si91x_ulp_timer.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_ulp_timer/sl_si91x_ulp_timer.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/sl_si91x_ulp_timer-brd4325c
make -C output/sl_si91x_ulp_timer-brd4325c -f sl_si91x_ulp_timer.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_ulp_timer/sl_si91x_ulp_timer.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/sl_si91x_ulp_timer-brd4325g
make -C output/sl_si91x_ulp_timer-brd4325g -f sl_si91x_ulp_timer.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_ulp_uart/sl_si91x_ulp_uart.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/sl_si91x_ulp_uart-brd4325a
make -C output/sl_si91x_ulp_uart-brd4325a -f sl_si91x_ulp_uart.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_ulp_uart/sl_si91x_ulp_uart.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/sl_si91x_ulp_uart-brd4325c
make -C output/sl_si91x_ulp_uart-brd4325c -f sl_si91x_ulp_uart.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_ulp_uart/sl_si91x_ulp_uart.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/sl_si91x_ulp_uart-brd4325g
make -C output/sl_si91x_ulp_uart-brd4325g -f sl_si91x_ulp_uart.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_usart/sl_si91x_usart.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/sl_si91x_usart-brd4325a
make -C output/sl_si91x_usart-brd4325a -f sl_si91x_usart.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_usart/sl_si91x_usart.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/sl_si91x_usart-brd4325c
make -C output/sl_si91x_usart-brd4325c -f sl_si91x_usart.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_usart/sl_si91x_usart.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/sl_si91x_usart-brd4325g
make -C output/sl_si91x_usart-brd4325g -f sl_si91x_usart.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_watchdog_timer/sl_si91x_watchdog_timer.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/sl_si91x_watchdog_timer-brd4325a
make -C output/sl_si91x_watchdog_timer-brd4325a -f sl_si91x_watchdog_timer.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_watchdog_timer/sl_si91x_watchdog_timer.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/sl_si91x_watchdog_timer-brd4325c
make -C output/sl_si91x_watchdog_timer-brd4325c -f sl_si91x_watchdog_timer.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/peripheral/sl_si91x_watchdog_timer/sl_si91x_watchdog_timer.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/sl_si91x_watchdog_timer-brd4325g
make -C output/sl_si91x_watchdog_timer-brd4325g -f sl_si91x_watchdog_timer.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/wlan/tcp_tx_on_periodic_wakeup/tcp_tx_on_periodic_wakeup_soc.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/tcp_tx_on_periodic_wakeup_soc-brd4325a
make -C output/tcp_tx_on_periodic_wakeup_soc-brd4325a -f tcp_tx_on_periodic_wakeup_soc.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/wlan/tcp_tx_on_periodic_wakeup/tcp_tx_on_periodic_wakeup_soc.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/tcp_tx_on_periodic_wakeup_soc-brd4325c
make -C output/tcp_tx_on_periodic_wakeup_soc-brd4325c -f tcp_tx_on_periodic_wakeup_soc.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/wlan/tcp_tx_on_periodic_wakeup/tcp_tx_on_periodic_wakeup_soc.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/tcp_tx_on_periodic_wakeup_soc-brd4325g
make -C output/tcp_tx_on_periodic_wakeup_soc-brd4325g -f tcp_tx_on_periodic_wakeup_soc.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan/twt_use_case_remote_app/twt_use_case_remote_app.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/twt_use_case_remote_app-brd4325a
make -C output/twt_use_case_remote_app-brd4325a -f twt_use_case_remote_app.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan/twt_use_case_remote_app/twt_use_case_remote_app.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/twt_use_case_remote_app-brd4325c
make -C output/twt_use_case_remote_app-brd4325c -f twt_use_case_remote_app.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan/twt_use_case_remote_app/twt_use_case_remote_app.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/twt_use_case_remote_app-brd4325g
make -C output/twt_use_case_remote_app-brd4325g -f twt_use_case_remote_app.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan/wifi6_twt_use_case_demo/wifi6_twt_use_case_demo.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/wifi6_twt_use_case_demo-brd4325a
make -C output/wifi6_twt_use_case_demo-brd4325a -f wifi6_twt_use_case_demo.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan/wifi6_twt_use_case_demo/wifi6_twt_use_case_demo.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/wifi6_twt_use_case_demo-brd4325c
make -C output/wifi6_twt_use_case_demo-brd4325c -f wifi6_twt_use_case_demo.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan/wifi6_twt_use_case_demo/wifi6_twt_use_case_demo.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/wifi6_twt_use_case_demo-brd4325g
make -C output/wifi6_twt_use_case_demo-brd4325g -f wifi6_twt_use_case_demo.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan/access_point/access_point_ncp.slcp --force --with "brd4180b" -np -d output/wifi_access_point_ncp-brd4180b
make -C output/wifi_access_point_ncp-brd4180b -f wifi_access_point_ncp.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan/access_point/access_point_soc.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/wifi_access_point_soc-brd4325a
make -C output/wifi_access_point_soc-brd4325a -f wifi_access_point_soc.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan/access_point/access_point_soc.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/wifi_access_point_soc-brd4325c
make -C output/wifi_access_point_soc-brd4325c -f wifi_access_point_soc.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan/access_point/access_point_soc.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/wifi_access_point_soc-brd4325g
make -C output/wifi_access_point_soc-brd4325g -f wifi_access_point_soc.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/featured/aws_device_shadow/aws_device_shadow_ncp.slcp --force --with "brd4180b" -np -d output/wifi_aws_device_shadow_ncp-brd4180b
make -C output/wifi_aws_device_shadow_ncp-brd4180b -f wifi_aws_device_shadow_ncp.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/featured/aws_device_shadow/aws_device_shadow_soc.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/wifi_aws_device_shadow_soc-brd4325a
make -C output/wifi_aws_device_shadow_soc-brd4325a -f wifi_aws_device_shadow_soc.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/featured/aws_device_shadow/aws_device_shadow_soc.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/wifi_aws_device_shadow_soc-brd4325c
make -C output/wifi_aws_device_shadow_soc-brd4325c -f wifi_aws_device_shadow_soc.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/featured/aws_device_shadow/aws_device_shadow_soc.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/wifi_aws_device_shadow_soc-brd4325g
make -C output/wifi_aws_device_shadow_soc-brd4325g -f wifi_aws_device_shadow_soc.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan/cloud_apps/aws/mqtt/aws_mqtt_ncp.slcp --force --with "brd4180b" -np -d output/wifi_aws_mqtt_ncp-brd4180b
make -C output/wifi_aws_mqtt_ncp-brd4180b -f wifi_aws_mqtt_ncp.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan/cloud_apps/aws/mqtt/aws_mqtt_soc.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/wifi_aws_mqtt_soc-brd4325a
make -C output/wifi_aws_mqtt_soc-brd4325a -f wifi_aws_mqtt_soc.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan/cloud_apps/aws/mqtt/aws_mqtt_soc.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/wifi_aws_mqtt_soc-brd4325c
make -C output/wifi_aws_mqtt_soc-brd4325c -f wifi_aws_mqtt_soc.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan/cloud_apps/aws/mqtt/aws_mqtt_soc.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/wifi_aws_mqtt_soc-brd4325g
make -C output/wifi_aws_mqtt_soc-brd4325g -f wifi_aws_mqtt_soc.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan/calibration_app/calibration_app_ncp.slcp --force --with "brd4180b" -np -d output/wifi_calibration_app_ncp-brd4180b
make -C output/wifi_calibration_app_ncp-brd4180b -f wifi_calibration_app_ncp.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan/calibration_app/calibration_app_soc.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/wifi_calibration_app_soc-brd4325a
make -C output/wifi_calibration_app_soc-brd4325a -f wifi_calibration_app_soc.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan/calibration_app/calibration_app_soc.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/wifi_calibration_app_soc-brd4325c
make -C output/wifi_calibration_app_soc-brd4325c -f wifi_calibration_app_soc.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan/calibration_app/calibration_app_soc.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/wifi_calibration_app_soc-brd4325g
make -C output/wifi_calibration_app_soc-brd4325g -f wifi_calibration_app_soc.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan/concurrent_mode/concurrent_mode_ncp.slcp --force --with "brd4180b" -np -d output/wifi_concurrent_mode_ncp-brd4180b
make -C output/wifi_concurrent_mode_ncp-brd4180b -f wifi_concurrent_mode_ncp.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan/concurrent_mode/concurrent_mode_soc.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/wifi_concurrent_mode_soc-brd4325a
make -C output/wifi_concurrent_mode_soc-brd4325a -f wifi_concurrent_mode_soc.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan/concurrent_mode/concurrent_mode_soc.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/wifi_concurrent_mode_soc-brd4325c
make -C output/wifi_concurrent_mode_soc-brd4325c -f wifi_concurrent_mode_soc.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan/concurrent_mode/concurrent_mode_soc.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/wifi_concurrent_mode_soc-brd4325g
make -C output/wifi_concurrent_mode_soc-brd4325g -f wifi_concurrent_mode_soc.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan/embedded_mqtt_client/embedded_mqtt_client_ncp.slcp --force --with "brd4180b" -np -d output/wifi_embedded_mqtt_client_ncp-brd4180b
make -C output/wifi_embedded_mqtt_client_ncp-brd4180b -f wifi_embedded_mqtt_client_ncp.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan/embedded_mqtt_client/embedded_mqtt_client_soc.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/wifi_embedded_mqtt_client_soc-brd4325a
make -C output/wifi_embedded_mqtt_client_soc-brd4325a -f wifi_embedded_mqtt_client_soc.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan/embedded_mqtt_client/embedded_mqtt_client_soc.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/wifi_embedded_mqtt_client_soc-brd4325c
make -C output/wifi_embedded_mqtt_client_soc-brd4325c -f wifi_embedded_mqtt_client_soc.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan/embedded_mqtt_client/embedded_mqtt_client_soc.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/wifi_embedded_mqtt_client_soc-brd4325g
make -C output/wifi_embedded_mqtt_client_soc-brd4325g -f wifi_embedded_mqtt_client_soc.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan/embedded_mqtt_client_twt/embedded_mqtt_client_twt.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/wifi_embedded_mqtt_client_twt-brd4325a
make -C output/wifi_embedded_mqtt_client_twt-brd4325a -f wifi_embedded_mqtt_client_twt.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan/embedded_mqtt_client_twt/embedded_mqtt_client_twt.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/wifi_embedded_mqtt_client_twt-brd4325c
make -C output/wifi_embedded_mqtt_client_twt-brd4325c -f wifi_embedded_mqtt_client_twt.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan/embedded_mqtt_client_twt/embedded_mqtt_client_twt.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/wifi_embedded_mqtt_client_twt-brd4325g
make -C output/wifi_embedded_mqtt_client_twt-brd4325g -f wifi_embedded_mqtt_client_twt.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan/sntp_client/sntp_client_ncp.slcp --force --with "brd4180b" -np -d output/wifi_embedded_sntp_client_ncp-brd4180b
make -C output/wifi_embedded_sntp_client_ncp-brd4180b -f wifi_embedded_sntp_client_ncp.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan/sntp_client/sntp_client_soc.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/wifi_embedded_sntp_client_soc-brd4325a
make -C output/wifi_embedded_sntp_client_soc-brd4325a -f wifi_embedded_sntp_client_soc.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan/sntp_client/sntp_client_soc.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/wifi_embedded_sntp_client_soc-brd4325c
make -C output/wifi_embedded_sntp_client_soc-brd4325c -f wifi_embedded_sntp_client_soc.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan/sntp_client/sntp_client_soc.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/wifi_embedded_sntp_client_soc-brd4325g
make -C output/wifi_embedded_sntp_client_soc-brd4325g -f wifi_embedded_sntp_client_soc.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan/enterprise_client/enterprise_client_ncp.slcp --force --with "brd4180b" -np -d output/wifi_enterprise_client_ncp-brd4180b
make -C output/wifi_enterprise_client_ncp-brd4180b -f wifi_enterprise_client_ncp.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan/enterprise_client/enterprise_client_soc.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/wifi_enterprise_client_soc-brd4325a
make -C output/wifi_enterprise_client_soc-brd4325a -f wifi_enterprise_client_soc.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan/enterprise_client/enterprise_client_soc.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/wifi_enterprise_client_soc-brd4325c
make -C output/wifi_enterprise_client_soc-brd4325c -f wifi_enterprise_client_soc.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan/enterprise_client/enterprise_client_soc.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/wifi_enterprise_client_soc-brd4325g
make -C output/wifi_enterprise_client_soc-brd4325g -f wifi_enterprise_client_soc.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/featured/firmware_update/firmware_update_ncp.slcp --force --with "brd4180b" -np -d output/wifi_firmware_update_ncp-brd4180b
make -C output/wifi_firmware_update_ncp-brd4180b -f wifi_firmware_update_ncp.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/featured/firmware_update/firmware_update_soc.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/wifi_firmware_update_soc-brd4325a
make -C output/wifi_firmware_update_soc-brd4325a -f wifi_firmware_update_soc.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/featured/firmware_update/firmware_update_soc.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/wifi_firmware_update_soc-brd4325c
make -C output/wifi_firmware_update_soc-brd4325c -f wifi_firmware_update_soc.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/featured/firmware_update/firmware_update_soc.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/wifi_firmware_update_soc-brd4325g
make -C output/wifi_firmware_update_soc-brd4325g -f wifi_firmware_update_soc.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan/http_otaf/http_otaf.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/wifi_http_otaf-brd4325a
make -C output/wifi_http_otaf-brd4325a -f wifi_http_otaf.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan/http_otaf/http_otaf.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/wifi_http_otaf-brd4325c
make -C output/wifi_http_otaf-brd4325c -f wifi_http_otaf.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan/http_otaf/http_otaf.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/wifi_http_otaf-brd4325g
make -C output/wifi_http_otaf-brd4325g -f wifi_http_otaf.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan_ble/wifi_https_ble_dual_role/wifi_https_ble_dual_role.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/wifi_https_ble_dual_role-brd4325a
make -C output/wifi_https_ble_dual_role-brd4325a -f wifi_https_ble_dual_role.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan_ble/wifi_https_ble_dual_role/wifi_https_ble_dual_role.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/wifi_https_ble_dual_role-brd4325c
make -C output/wifi_https_ble_dual_role-brd4325c -f wifi_https_ble_dual_role.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan_ble/wifi_https_ble_dual_role/wifi_https_ble_dual_role.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/wifi_https_ble_dual_role-brd4325g
make -C output/wifi_https_ble_dual_role-brd4325g -f wifi_https_ble_dual_role.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan/lwip_tcp_client/lwip_tcp_client_ncp.slcp --force --with "brd4180b" -np -d output/wifi_lwip_tcp_client_ncp-brd4180b
make -C output/wifi_lwip_tcp_client_ncp-brd4180b -f wifi_lwip_tcp_client_ncp.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan/lwip_tcp_client/lwip_tcp_client_soc.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/wifi_lwip_tcp_client_soc-brd4325a
make -C output/wifi_lwip_tcp_client_soc-brd4325a -f wifi_lwip_tcp_client_soc.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan/lwip_tcp_client/lwip_tcp_client_soc.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/wifi_lwip_tcp_client_soc-brd4325c
make -C output/wifi_lwip_tcp_client_soc-brd4325c -f wifi_lwip_tcp_client_soc.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan/lwip_tcp_client/lwip_tcp_client_soc.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/wifi_lwip_tcp_client_soc-brd4325g
make -C output/wifi_lwip_tcp_client_soc-brd4325g -f wifi_lwip_tcp_client_soc.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/wlan/m4_firmware_update/m4_firmware_update.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/wifi_m4_firmware_update-brd4325a
make -C output/wifi_m4_firmware_update-brd4325a -f wifi_m4_firmware_update.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/wlan/m4_firmware_update/m4_firmware_update.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/wifi_m4_firmware_update-brd4325c
make -C output/wifi_m4_firmware_update-brd4325c -f wifi_m4_firmware_update.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/si91x_soc/wlan/m4_firmware_update/m4_firmware_update.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/wifi_m4_firmware_update-brd4325g
make -C output/wifi_m4_firmware_update-brd4325g -f wifi_m4_firmware_update.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan/power_save_deep_sleep/power_save_deep_sleep_ncp.slcp --force --with "brd4180b" -np -d output/wifi_power_save_deep_sleep_ncp-brd4180b
make -C output/wifi_power_save_deep_sleep_ncp-brd4180b -f wifi_power_save_deep_sleep_ncp.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan/power_save_deep_sleep/power_save_deep_sleep_soc.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/wifi_power_save_deep_sleep_soc-brd4325a
make -C output/wifi_power_save_deep_sleep_soc-brd4325a -f wifi_power_save_deep_sleep_soc.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan/power_save_deep_sleep/power_save_deep_sleep_soc.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/wifi_power_save_deep_sleep_soc-brd4325c
make -C output/wifi_power_save_deep_sleep_soc-brd4325c -f wifi_power_save_deep_sleep_soc.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan/power_save_deep_sleep/power_save_deep_sleep_soc.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/wifi_power_save_deep_sleep_soc-brd4325g
make -C output/wifi_power_save_deep_sleep_soc-brd4325g -f wifi_power_save_deep_sleep_soc.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/featured/powersave_standby_associated/powersave_standby_associated_ncp.slcp --force --with "brd4180b" -np -d output/wifi_powersave_standby_associated_ncp-brd4180b
make -C output/wifi_powersave_standby_associated_ncp-brd4180b -f wifi_powersave_standby_associated_ncp.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/featured/powersave_standby_associated/powersave_standby_associated_soc.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/wifi_powersave_standby_associated_soc-brd4325a
make -C output/wifi_powersave_standby_associated_soc-brd4325a -f wifi_powersave_standby_associated_soc.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/featured/powersave_standby_associated/powersave_standby_associated_soc.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/wifi_powersave_standby_associated_soc-brd4325c
make -C output/wifi_powersave_standby_associated_soc-brd4325c -f wifi_powersave_standby_associated_soc.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/featured/powersave_standby_associated/powersave_standby_associated_soc.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/wifi_powersave_standby_associated_soc-brd4325g
make -C output/wifi_powersave_standby_associated_soc-brd4325g -f wifi_powersave_standby_associated_soc.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan/select_app/select_app_ncp.slcp --force --with "brd4180b" -np -d output/wifi_select_app_ncp-brd4180b
make -C output/wifi_select_app_ncp-brd4180b -f wifi_select_app_ncp.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan/select_app/select_app_soc.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/wifi_select_app_soc-brd4325a
make -C output/wifi_select_app_soc-brd4325a -f wifi_select_app_soc.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan/select_app/select_app_soc.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/wifi_select_app_soc-brd4325c
make -C output/wifi_select_app_soc-brd4325c -f wifi_select_app_soc.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan/select_app/select_app_soc.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/wifi_select_app_soc-brd4325g
make -C output/wifi_select_app_soc-brd4325g -f wifi_select_app_soc.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan_ble/wifi_station_ble_provisioning_aws/wifi_station_ble_provisioning_aws_ncp.slcp --force --with "brd4180b" -np -d output/wifi_station_ble_provisioning_aws_ncp-brd4180b
make -C output/wifi_station_ble_provisioning_aws_ncp-brd4180b -f wifi_station_ble_provisioning_aws_ncp.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan_ble/wifi_station_ble_provisioning_aws/wifi_station_ble_provisioning_aws_soc.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/wifi_station_ble_provisioning_aws_soc-brd4325a
make -C output/wifi_station_ble_provisioning_aws_soc-brd4325a -f wifi_station_ble_provisioning_aws_soc.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan_ble/wifi_station_ble_provisioning_aws/wifi_station_ble_provisioning_aws_soc.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/wifi_station_ble_provisioning_aws_soc-brd4325c
make -C output/wifi_station_ble_provisioning_aws_soc-brd4325c -f wifi_station_ble_provisioning_aws_soc.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan_ble/wifi_station_ble_provisioning_aws/wifi_station_ble_provisioning_aws_soc.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/wifi_station_ble_provisioning_aws_soc-brd4325g
make -C output/wifi_station_ble_provisioning_aws_soc-brd4325g -f wifi_station_ble_provisioning_aws_soc.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan_ble/wifi_station_ble_provisioning/wifi_station_ble_provisioning_ncp.slcp --force --with "brd4180b" -np -d output/wifi_station_ble_provisioning_ncp-brd4180b
make -C output/wifi_station_ble_provisioning_ncp-brd4180b -f wifi_station_ble_provisioning_ncp.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan_ble/wifi_station_ble_provisioning/wifi_station_ble_provisioning_soc.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/wifi_station_ble_provisioning_soc-brd4325a
make -C output/wifi_station_ble_provisioning_soc-brd4325a -f wifi_station_ble_provisioning_soc.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan_ble/wifi_station_ble_provisioning/wifi_station_ble_provisioning_soc.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/wifi_station_ble_provisioning_soc-brd4325c
make -C output/wifi_station_ble_provisioning_soc-brd4325c -f wifi_station_ble_provisioning_soc.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan_ble/wifi_station_ble_provisioning/wifi_station_ble_provisioning_soc.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/wifi_station_ble_provisioning_soc-brd4325g
make -C output/wifi_station_ble_provisioning_soc-brd4325g -f wifi_station_ble_provisioning_soc.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan_ble/wifi_station_ble_throughput_app/wifi_station_ble_throughput_app.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/wifi_station_ble_throughput_app-brd4325a
make -C output/wifi_station_ble_throughput_app-brd4325a -f wifi_station_ble_throughput_app.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan_ble/wifi_station_ble_throughput_app/wifi_station_ble_throughput_app.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/wifi_station_ble_throughput_app-brd4325c
make -C output/wifi_station_ble_throughput_app-brd4325c -f wifi_station_ble_throughput_app.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan_ble/wifi_station_ble_throughput_app/wifi_station_ble_throughput_app.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/wifi_station_ble_throughput_app-brd4325g
make -C output/wifi_station_ble_throughput_app-brd4325g -f wifi_station_ble_throughput_app.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan/station_ping/station_ping_ncp.slcp --force --with "brd4180b" -np -d output/wifi_station_ping_ncp-brd4180b
make -C output/wifi_station_ping_ncp-brd4180b -f wifi_station_ping_ncp.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan/station_ping/station_ping_soc.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/wifi_station_ping_soc-brd4325a
make -C output/wifi_station_ping_soc-brd4325a -f wifi_station_ping_soc.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan/station_ping/station_ping_soc.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/wifi_station_ping_soc-brd4325c
make -C output/wifi_station_ping_soc-brd4325c -f wifi_station_ping_soc.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan/station_ping/station_ping_soc.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/wifi_station_ping_soc-brd4325g
make -C output/wifi_station_ping_soc-brd4325g -f wifi_station_ping_soc.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan/station_ping_v6/station_ping_v6.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/wifi_station_ping_v6-brd4325a
make -C output/wifi_station_ping_v6-brd4325a -f wifi_station_ping_v6.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan/station_ping_v6/station_ping_v6.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/wifi_station_ping_v6-brd4325c
make -C output/wifi_station_ping_v6-brd4325c -f wifi_station_ping_v6.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan/station_ping_v6/station_ping_v6.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/wifi_station_ping_v6-brd4325g
make -C output/wifi_station_ping_v6-brd4325g -f wifi_station_ping_v6.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan/three_ssl_concurrent_client_sockets/three_ssl_client_sockets.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/wifi_three_ssl_client_sockets-brd4325a
make -C output/wifi_three_ssl_client_sockets-brd4325a -f wifi_three_ssl_client_sockets.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan/three_ssl_concurrent_client_sockets/three_ssl_client_sockets.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/wifi_three_ssl_client_sockets-brd4325c
make -C output/wifi_three_ssl_client_sockets-brd4325c -f wifi_three_ssl_client_sockets.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan/three_ssl_concurrent_client_sockets/three_ssl_client_sockets.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/wifi_three_ssl_client_sockets-brd4325g
make -C output/wifi_three_ssl_client_sockets-brd4325g -f wifi_three_ssl_client_sockets.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan_ble/wifi_throughput_ble_dual_role/wifi_throughput_ble_dual_role.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/wifi_throughput_ble_dual_role-brd4325a
make -C output/wifi_throughput_ble_dual_role-brd4325a -f wifi_throughput_ble_dual_role.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan_ble/wifi_throughput_ble_dual_role/wifi_throughput_ble_dual_role.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/wifi_throughput_ble_dual_role-brd4325c
make -C output/wifi_throughput_ble_dual_role-brd4325c -f wifi_throughput_ble_dual_role.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan_ble/wifi_throughput_ble_dual_role/wifi_throughput_ble_dual_role.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/wifi_throughput_ble_dual_role-brd4325g
make -C output/wifi_throughput_ble_dual_role-brd4325g -f wifi_throughput_ble_dual_role.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan/tls_client/tls_client_ncp.slcp --force --with "brd4180b" -np -d output/wifi_tls_client_ncp-brd4180b
make -C output/wifi_tls_client_ncp-brd4180b -f wifi_tls_client_ncp.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan/tls_client/tls_client_soc.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/wifi_tls_client_soc-brd4325a
make -C output/wifi_tls_client_soc-brd4325a -f wifi_tls_client_soc.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan/tls_client/tls_client_soc.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/wifi_tls_client_soc-brd4325c
make -C output/wifi_tls_client_soc-brd4325c -f wifi_tls_client_soc.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan/tls_client/tls_client_soc.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/wifi_tls_client_soc-brd4325g
make -C output/wifi_tls_client_soc-brd4325g -f wifi_tls_client_soc.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan/twt_tcp_client/twt_tcp_client_ncp.slcp --force --with "brd4180b" -np -d output/wifi_twt_tcp_client_ncp-brd4180b
make -C output/wifi_twt_tcp_client_ncp-brd4180b -f wifi_twt_tcp_client_ncp.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan/twt_tcp_client/twt_tcp_client_soc.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/wifi_twt_tcp_client_soc-brd4325a
make -C output/wifi_twt_tcp_client_soc-brd4325a -f wifi_twt_tcp_client_soc.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan/twt_tcp_client/twt_tcp_client_soc.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/wifi_twt_tcp_client_soc-brd4325c
make -C output/wifi_twt_tcp_client_soc-brd4325c -f wifi_twt_tcp_client_soc.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan/twt_tcp_client/twt_tcp_client_soc.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/wifi_twt_tcp_client_soc-brd4325g
make -C output/wifi_twt_tcp_client_soc-brd4325g -f wifi_twt_tcp_client_soc.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan/user_gain_table/user_gain_table_ncp.slcp --force --with "brd4180b" -np -d output/wifi_user_gain_table_ncp-brd4180b
make -C output/wifi_user_gain_table_ncp-brd4180b -f wifi_user_gain_table_ncp.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan/user_gain_table/user_gain_table_soc.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/wifi_user_gain_table_soc-brd4325a
make -C output/wifi_user_gain_table_soc-brd4325a -f wifi_user_gain_table_soc.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan/user_gain_table/user_gain_table_soc.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/wifi_user_gain_table_soc-brd4325c
make -C output/wifi_user_gain_table_soc-brd4325c -f wifi_user_gain_table_soc.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan/user_gain_table/user_gain_table_soc.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/wifi_user_gain_table_soc-brd4325g
make -C output/wifi_user_gain_table_soc-brd4325g -f wifi_user_gain_table_soc.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/featured/wlan_throughput/wlan_throughput_ncp.slcp --force --with "brd4180b" -np -d output/wifi_wlan_throughput_ncp-brd4180b
make -C output/wifi_wlan_throughput_ncp-brd4180b -f wifi_wlan_throughput_ncp.Makefile -j$((`nproc`/4))


/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/featured/wlan_throughput/wlan_throughput_soc.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/wifi_wlan_throughput_soc-brd4325a
make -C output/wifi_wlan_throughput_soc-brd4325a -f wifi_wlan_throughput_soc.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/featured/wlan_throughput/wlan_throughput_soc.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/wifi_wlan_throughput_soc-brd4325c
make -C output/wifi_wlan_throughput_soc-brd4325c -f wifi_wlan_throughput_soc.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/featured/wlan_throughput/wlan_throughput_soc.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/wifi_wlan_throughput_soc-brd4325g
make -C output/wifi_wlan_throughput_soc-brd4325g -f wifi_wlan_throughput_soc.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan/wlan_throughput_v6/wlan_throughput_v6_ncp.slcp --force --with "brd4180b" -np -d output/wifi_wlan_throughput_v6_ncp-brd4180b
make -C output/wifi_wlan_throughput_v6_ncp-brd4180b -f wifi_wlan_throughput_v6_ncp.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan/wlan_throughput_v6/wlan_throughput_v6_soc.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/wifi_wlan_throughput_v6_soc-brd4325a
make -C output/wifi_wlan_throughput_v6_soc-brd4325a -f wifi_wlan_throughput_v6_soc.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan/wlan_throughput_v6/wlan_throughput_v6_soc.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/wifi_wlan_throughput_v6_soc-brd4325c
make -C output/wifi_wlan_throughput_v6_soc-brd4325c -f wifi_wlan_throughput_v6_soc.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan/wlan_throughput_v6/wlan_throughput_v6_soc.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/wifi_wlan_throughput_v6_soc-brd4325g
make -C output/wifi_wlan_throughput_v6_soc-brd4325g -f wifi_wlan_throughput_v6_soc.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan/wlan_rf_test/wlan_rf_test_ncp.slcp --force --with "brd4180b" -np -d output/wlan_rf_test_ncp-brd4180b
make -C output/wlan_rf_test_ncp-brd4180b -f wlan_rf_test_ncp.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan/wlan_rf_test/wlan_rf_test_soc.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/wlan_rf_test_soc-brd4325a
make -C output/wlan_rf_test_soc-brd4325a -f wlan_rf_test_soc.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan/wlan_rf_test/wlan_rf_test_soc.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/wlan_rf_test_soc-brd4325c
make -C output/wlan_rf_test_soc-brd4325c -f wlan_rf_test_soc.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/snippets/wlan/wlan_rf_test/wlan_rf_test_soc.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/wlan_rf_test_soc-brd4325g
make -C output/wlan_rf_test_soc-brd4325g -f wlan_rf_test_soc.Makefile -j$((`nproc`/4))


/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/ble/battery_service/battery_service.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/ble_battery_service-brd4325a
make -C output/ble_battery_service-brd4325a -f ble_battery_service.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/ble/battery_service/battery_service.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/ble_battery_service-brd4325c
make -C output/ble_battery_service-brd4325c -f ble_battery_service.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/ble/battery_service/battery_service.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/ble_battery_service-brd4325g
make -C output/ble_battery_service-brd4325g -f ble_battery_service.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/ble/ble_chat/ble_chat.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/ble_chat-brd4325a
make -C output/ble_chat-brd4325a -f ble_chat.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/ble/ble_chat/ble_chat.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/ble_chat-brd4325c
make -C output/ble_chat-brd4325c -f ble_chat.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/ble/ble_chat/ble_chat.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/ble_chat-brd4325g
make -C output/ble_chat-brd4325g -f ble_chat.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/ble/ble_peripheral/ble_peripheral.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/ble_peripheral-brd4325a
make -C output/ble_peripheral-brd4325a -f ble_peripheral.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/ble/ble_peripheral/ble_peripheral.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/ble_peripheral-brd4325c
make -C output/ble_peripheral-brd4325c -f ble_peripheral.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/ble/ble_peripheral/ble_peripheral.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/ble_peripheral-brd4325g
make -C output/ble_peripheral-brd4325g -f ble_peripheral.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/ble/ble_simple_smp/ble_simple_smp.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/ble_simple_smp-brd4325a
make -C output/ble_simple_smp-brd4325a -f ble_simple_smp.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/ble/ble_simple_smp/ble_simple_smp.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/ble_simple_smp-brd4325c
make -C output/ble_simple_smp-brd4325c -f ble_simple_smp.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/ble/ble_simple_smp/ble_simple_smp.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/ble_simple_smp-brd4325g
make -C output/ble_simple_smp-brd4325g -f ble_simple_smp.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/ble/blood_pressure/blood_pressure.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/blood_pressure-brd4325a
make -C output/blood_pressure-brd4325a -f blood_pressure.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/ble/blood_pressure/blood_pressure.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/blood_pressure-brd4325c
make -C output/blood_pressure-brd4325c -f blood_pressure.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/ble/blood_pressure/blood_pressure.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/blood_pressure-brd4325g
make -C output/blood_pressure-brd4325g -f blood_pressure.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/ble/gatt_test/gatt_test_ncp.slcp --force --with "brd4180b" -np -d output/gatt_test_ncp-brd4180b
make -C output/gatt_test_ncp-brd4180b -f gatt_test_ncp.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/ble/gatt_test/gatt_test_soc.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/gatt_test_soc-brd4325a
make -C output/gatt_test_soc-brd4325a -f gatt_test_soc.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/ble/gatt_test/gatt_test_soc.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/gatt_test_soc-brd4325c
make -C output/gatt_test_soc-brd4325c -f gatt_test_soc.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/ble/gatt_test/gatt_test_soc.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/gatt_test_soc-brd4325g
make -C output/gatt_test_soc-brd4325g -f gatt_test_soc.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/ble/glucose/glucose.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/glucose-brd4325a
make -C output/glucose-brd4325a -f glucose.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/ble/glucose/glucose.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/glucose-brd4325c
make -C output/glucose-brd4325c -f glucose.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/ble/glucose/glucose.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/glucose-brd4325g
make -C output/glucose-brd4325g -f glucose.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/ble/health_thermometer/health_thermometer.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/health_thermometer-brd4325a
make -C output/health_thermometer-brd4325a -f health_thermometer.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/ble/health_thermometer/health_thermometer.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/health_thermometer-brd4325c
make -C output/health_thermometer-brd4325c -f health_thermometer.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/ble/health_thermometer/health_thermometer.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/health_thermometer-brd4325g
make -C output/health_thermometer-brd4325g -f health_thermometer.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/ble/immediate_alert_client/immediate_alert_client_ncp.slcp --force --with "brd4180b" -np -d output/immediate_alert_client_ncp-brd4180b
make -C output/immediate_alert_client_ncp-brd4180b -f immediate_alert_client_ncp.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/ble/immediate_alert_client/immediate_alert_client_soc.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/immediate_alert_client_soc-brd4325a
make -C output/immediate_alert_client_soc-brd4325a -f immediate_alert_client_soc.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/ble/immediate_alert_client/immediate_alert_client_soc.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/immediate_alert_client_soc-brd4325c
make -C output/immediate_alert_client_soc-brd4325c -f immediate_alert_client_soc.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/ble/immediate_alert_client/immediate_alert_client_soc.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/immediate_alert_client_soc-brd4325g
make -C output/immediate_alert_client_soc-brd4325g -f immediate_alert_client_soc.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/ble/proximity_profile/proximity_profile.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/proximity_profile-brd4325a
make -C output/proximity_profile-brd4325a -f proximity_profile.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/ble/proximity_profile/proximity_profile.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/proximity_profile-brd4325c
make -C output/proximity_profile-brd4325c -f proximity_profile.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/ble/proximity_profile/proximity_profile.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/proximity_profile-brd4325g
make -C output/proximity_profile-brd4325g -f proximity_profile.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/wlan/aws_device_shadow_logging_stats/aws_device_shadow_logging_stats_ncp.slcp --force --with "brd4180b" -np -d output/wifi_aws_device_shadow_logging_stats_ncp-brd4180b
make -C output/wifi_aws_device_shadow_logging_stats_ncp-brd4180b -f wifi_aws_device_shadow_logging_stats_ncp.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/wlan/aws_device_shadow_logging_stats/aws_device_shadow_logging_stats_soc.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/wifi_aws_device_shadow_logging_stats_soc-brd4325a
make -C output/wifi_aws_device_shadow_logging_stats_soc-brd4325a -f wifi_aws_device_shadow_logging_stats_soc.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/wlan/aws_device_shadow_logging_stats/aws_device_shadow_logging_stats_soc.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/wifi_aws_device_shadow_logging_stats_soc-brd4325c
make -C output/wifi_aws_device_shadow_logging_stats_soc-brd4325c -f wifi_aws_device_shadow_logging_stats_soc.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/wlan/aws_device_shadow_logging_stats/aws_device_shadow_logging_stats_soc.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/wifi_aws_device_shadow_logging_stats_soc-brd4325g
make -C output/wifi_aws_device_shadow_logging_stats_soc-brd4325g -f wifi_aws_device_shadow_logging_stats_soc.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/wlan_ble/wifi_ble_power_save/wifi_ble_power_save.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/wifi_ble_power_save-brd4325a
make -C output/wifi_ble_power_save-brd4325a -f wifi_ble_power_save.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/wlan_ble/wifi_ble_power_save/wifi_ble_power_save.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/wifi_ble_power_save-brd4325c
make -C output/wifi_ble_power_save-brd4325c -f wifi_ble_power_save.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/wlan_ble/wifi_ble_power_save/wifi_ble_power_save.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/wifi_ble_power_save-brd4325g
make -C output/wifi_ble_power_save-brd4325g -f wifi_ble_power_save.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/wlan/http_client/http_client_app.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/wifi_http_client_app-brd4325a
make -C output/wifi_http_client_app-brd4325a -f wifi_http_client_app.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/wlan/http_client/http_client_app.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/wifi_http_client_app-brd4325c
make -C output/wifi_http_client_app-brd4325c -f wifi_http_client_app.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/wlan/http_client/http_client_app.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/wifi_http_client_app-brd4325g
make -C output/wifi_http_client_app-brd4325g -f wifi_http_client_app.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/wlan/http_client_post_data/http_client_post_data_app.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/wifi_http_client_post_data-brd4325a
make -C output/wifi_http_client_post_data-brd4325a -f wifi_http_client_post_data.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/wlan/http_client_post_data/http_client_post_data_app.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/wifi_http_client_post_data-brd4325c
make -C output/wifi_http_client_post_data-brd4325c -f wifi_http_client_post_data.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/wlan/http_client_post_data/http_client_post_data_app.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/wifi_http_client_post_data-brd4325g
make -C output/wifi_http_client_post_data-brd4325g -f wifi_http_client_post_data.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/wlan_ble/wifi_https_ble_dual_role_v6/wifi_https_ble_dual_role_v6.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/wifi_https_ble_dual_role_v6-brd4325a
make -C output/wifi_https_ble_dual_role_v6-brd4325a -f wifi_https_ble_dual_role_v6.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/wlan_ble/wifi_https_ble_dual_role_v6/wifi_https_ble_dual_role_v6.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/wifi_https_ble_dual_role_v6-brd4325c
make -C output/wifi_https_ble_dual_role_v6-brd4325c -f wifi_https_ble_dual_role_v6.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/wlan_ble/wifi_https_ble_dual_role_v6/wifi_https_ble_dual_role_v6.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/wifi_https_ble_dual_role_v6-brd4325g
make -C output/wifi_https_ble_dual_role_v6-brd4325g -f wifi_https_ble_dual_role_v6.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/wlan/instant_bgscan/instant_bgscan.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/wifi_instant_bgscan-brd4325a
make -C output/wifi_instant_bgscan-brd4325a -f wifi_instant_bgscan.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/wlan/instant_bgscan/instant_bgscan.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/wifi_instant_bgscan-brd4325c
make -C output/wifi_instant_bgscan-brd4325c -f wifi_instant_bgscan.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/wlan/instant_bgscan/instant_bgscan.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/wifi_instant_bgscan-brd4325g
make -C output/wifi_instant_bgscan-brd4325g -f wifi_instant_bgscan.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/wlan/master_application/master_application_ncp.slcp --force --with "brd4180b" -np -d output/wifi_master_application_ncp-brd4180b
make -C output/wifi_master_application_ncp-brd4180b -f wifi_master_application_ncp.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/wlan/master_application/master_application_soc.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/wifi_master_application_soc-brd4325a
make -C output/wifi_master_application_soc-brd4325a -f wifi_master_application_soc.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/wlan/master_application/master_application_soc.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/wifi_master_application_soc-brd4325c
make -C output/wifi_master_application_soc-brd4325c -f wifi_master_application_soc.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/wlan/master_application/master_application_soc.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/wifi_master_application_soc-brd4325g
make -C output/wifi_master_application_soc-brd4325g -f wifi_master_application_soc.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/wlan/otaf/ota_firmware_update_app.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/wifi_ota_firmware_update_app-brd4325a
make -C output/wifi_ota_firmware_update_app-brd4325a -f wifi_ota_firmware_update_app.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/wlan/otaf/ota_firmware_update_app.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/wifi_ota_firmware_update_app-brd4325c
make -C output/wifi_ota_firmware_update_app-brd4325c -f wifi_ota_firmware_update_app.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/wlan/otaf/ota_firmware_update_app.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/wifi_ota_firmware_update_app-brd4325g
make -C output/wifi_ota_firmware_update_app-brd4325g -f wifi_ota_firmware_update_app.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/wlan/si91x_async_select_app/si91x_async_select_app_ncp.slcp --force --with "brd4180b" -np -d output/wifi_si91x_async_select_app_ncp-brd4180b
make -C output/wifi_si91x_async_select_app_ncp-brd4180b -f wifi_si91x_async_select_app_ncp.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/wlan/si91x_async_select_app/si91x_async_select_app_soc.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/wifi_si91x_async_select_app_soc-brd4325a
make -C output/wifi_si91x_async_select_app_soc-brd4325a -f wifi_si91x_async_select_app_soc.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/wlan/si91x_async_select_app/si91x_async_select_app_soc.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/wifi_si91x_async_select_app_soc-brd4325c
make -C output/wifi_si91x_async_select_app_soc-brd4325c -f wifi_si91x_async_select_app_soc.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/wlan/si91x_async_select_app/si91x_async_select_app_soc.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/wifi_si91x_async_select_app_soc-brd4325g
make -C output/wifi_si91x_async_select_app_soc-brd4325g -f wifi_si91x_async_select_app_soc.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/wlan/si91x_tcp_async_server/si91x_tcp_async_server.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/wifi_si91x_tcp_async_server-brd4325a
make -C output/wifi_si91x_tcp_async_server-brd4325a -f wifi_si91x_tcp_async_server.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/wlan/si91x_tcp_async_server/si91x_tcp_async_server.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/wifi_si91x_tcp_async_server-brd4325c
make -C output/wifi_si91x_tcp_async_server-brd4325c -f wifi_si91x_tcp_async_server.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/wlan/si91x_tcp_async_server/si91x_tcp_async_server.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/wifi_si91x_tcp_async_server-brd4325g
make -C output/wifi_si91x_tcp_async_server-brd4325g -f wifi_si91x_tcp_async_server.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/wlan/si91x_udp_async_receive/si91x_udp_async_receive.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/wifi_si91x_udp_async_receive-brd4325a
make -C output/wifi_si91x_udp_async_receive-brd4325a -f wifi_si91x_udp_async_receive.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/wlan/si91x_udp_async_receive/si91x_udp_async_receive.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/wifi_si91x_udp_async_receive-brd4325c
make -C output/wifi_si91x_udp_async_receive-brd4325c -f wifi_si91x_udp_async_receive.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/wlan/si91x_udp_async_receive/si91x_udp_async_receive.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/wifi_si91x_udp_async_receive-brd4325g
make -C output/wifi_si91x_udp_async_receive-brd4325g -f wifi_si91x_udp_async_receive.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/wlan/ssl_client/ssl_client.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/wifi_ssl_client-brd4325a
make -C output/wifi_ssl_client-brd4325a -f wifi_ssl_client.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/wlan/ssl_client/ssl_client.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/wifi_ssl_client-brd4325c
make -C output/wifi_ssl_client-brd4325c -f wifi_ssl_client.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/wlan/ssl_client/ssl_client.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/wifi_ssl_client-brd4325g
make -C output/wifi_ssl_client-brd4325g -f wifi_ssl_client.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/wlan_ble/wifi_station_ble_provisioning_aws_logging_stats/wifi_station_ble_provisioning_aws_logging_stats.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/wifi_station_ble_provisioning_aws_logging_stats-brd4325a
make -C output/wifi_station_ble_provisioning_aws_logging_stats-brd4325a -f wifi_station_ble_provisioning_aws_logging_stats.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/wlan_ble/wifi_station_ble_provisioning_aws_logging_stats/wifi_station_ble_provisioning_aws_logging_stats.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/wifi_station_ble_provisioning_aws_logging_stats-brd4325c
make -C output/wifi_station_ble_provisioning_aws_logging_stats-brd4325c -f wifi_station_ble_provisioning_aws_logging_stats.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/wlan_ble/wifi_station_ble_provisioning_aws_logging_stats/wifi_station_ble_provisioning_aws_logging_stats.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/wifi_station_ble_provisioning_aws_logging_stats-brd4325g
make -C output/wifi_station_ble_provisioning_aws_logging_stats-brd4325g -f wifi_station_ble_provisioning_aws_logging_stats.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/wlan/tcp_client_and_server/tcp_client_and_server.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/wifi_tcp_client_and_server-brd4325a
make -C output/wifi_tcp_client_and_server-brd4325a -f wifi_tcp_client_and_server.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/wlan/tcp_client_and_server/tcp_client_and_server.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/wifi_tcp_client_and_server-brd4325c
make -C output/wifi_tcp_client_and_server-brd4325c -f wifi_tcp_client_and_server.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/wlan/tcp_client_and_server/tcp_client_and_server.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/wifi_tcp_client_and_server-brd4325g
make -C output/wifi_tcp_client_and_server-brd4325g -f wifi_tcp_client_and_server.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/wlan/tcp_client/tcp_client_ncp.slcp --force --with "brd4180b" -np -d output/wifi_tcp_client_ncp-brd4180b
make -C output/wifi_tcp_client_ncp-brd4180b -f wifi_tcp_client_ncp.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/wlan/tcp_client/tcp_client_soc.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/wifi_tcp_client_soc-brd4325a
make -C output/wifi_tcp_client_soc-brd4325a -f wifi_tcp_client_soc.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/wlan/tcp_client/tcp_client_soc.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/wifi_tcp_client_soc-brd4325c
make -C output/wifi_tcp_client_soc-brd4325c -f wifi_tcp_client_soc.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/wlan/tcp_client/tcp_client_soc.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/wifi_tcp_client_soc-brd4325g
make -C output/wifi_tcp_client_soc-brd4325g -f wifi_tcp_client_soc.Makefile -j$((`nproc`/4))

/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/wlan/udp_client/udp_client.slcp --force --with "brd4325a;wiseconnect3_sdk" -np -d output/wifi_udp_client-brd4325a
make -C output/wifi_udp_client-brd4325a -f wifi_udp_client.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/wlan/udp_client/udp_client.slcp --force --with "brd4325c;wiseconnect3_sdk" -np -d output/wifi_udp_client-brd4325c
make -C output/wifi_udp_client-brd4325c -f wifi_udp_client.Makefile -j$((`nproc`/4))
/slc_cli/slc -daemon generate /gsdk/extension/wiseconnect3/examples/_internal/Wireless_Examples/wlan/udp_client/udp_client.slcp --force --with "brd4325g;wiseconnect3_sdk" -np -d output/wifi_udp_client-brd4325g
make -C output/wifi_udp_client-brd4325g -f wifi_udp_client.Makefile -j$((`nproc`/4))
