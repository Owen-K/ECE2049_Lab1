################################################################################
# Automatically-generated file. Do not edit!
################################################################################

<<<<<<< HEAD
SHELL = cmd.exe

=======
>>>>>>> 8ca88f4c3e99b3653fe82ff031a83efeb4f475ef
# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
<<<<<<< HEAD
	"C:/ti/ccs1200/ccs/tools/compiler/ti-cgt-msp430_21.6.0.LTS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="C:/ti/ccs1200/ccs/ccs_base/msp430/include" --include_path="C:/Users/Liam/Documents/WPI/A22/ECE2049/ECE2049_Lab1/ece2049a22_lab1_omkrause_lbjennings" --include_path="C:/ti/ccs1200/ccs/tools/compiler/ti-cgt-msp430_21.6.0.LTS/include" --advice:power=all --define=__MSP430F5529__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
=======
	"/Applications/ti/ccs1200/ccs/tools/compiler/ti-cgt-msp430_21.6.0.LTS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="/Applications/ti/ccs1200/ccs/ccs_base/msp430/include" --include_path="/Users/okrause/Documents/Classes/22-23/A22/ECE2049/CCS/Lab1/ece2049a22_lab1_omkrause_lbjennings/grlib" --include_path="/Users/okrause/Documents/Classes/22-23/A22/ECE2049/CCS/Lab1/ece2049a22_lab1_omkrause_lbjennings" --include_path="/Applications/ti/ccs1200/ccs/tools/compiler/ti-cgt-msp430_21.6.0.LTS/include" --advice:power=all --define=__MSP430F5529__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
>>>>>>> 8ca88f4c3e99b3653fe82ff031a83efeb4f475ef
	@echo 'Finished building: "$<"'
	@echo ' '

