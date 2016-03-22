#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-pic32mx.mk)" "nbproject/Makefile-local-pic32mx.mk"
include nbproject/Makefile-local-pic32mx.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=pic32mx
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/test_usart_sample.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/test_usart_sample.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../src/system_config/pic32mx/framework/system/clk/src/sys_clk_static.c ../src/system_config/pic32mx/framework/system/ports/src/sys_ports_static.c ../src/system_config/pic32mx/system_init.c ../src/system_config/pic32mx/system_interrupt.c ../src/system_config/pic32mx/system_exceptions.c ../src/system_config/pic32mx/system_tasks.c ../src/main.c ../src/test_app/app_test_drv_usart_basic_read_func.c ../src/test_app/app_test_drv_usart_basic_write_func.c ../src/app.c ../../../../bsp/pic32mx795_pim+e16/bsp_sys_init.c ../../../../framework/driver/usart/src/dynamic/drv_usart.c ../../../../framework/driver/usart/src/dynamic/drv_usart_read_write.c ../../../../framework/system/devcon/src/sys_devcon.c ../../../../framework/system/devcon/src/sys_devcon_pic32mx.c ../../../../framework/system/int/src/sys_int_pic32.c ../../../../framework/system/ports/src/sys_ports.c ../../../../framework/test/src/test_harness.c ../src/hvaf/data_class/data_class.c ../src/hvaf/ftmp/bus/ftmp_drv_usart/ftmp_drv_usart.c ../src/hvaf/ftmp/bus/ftmp_drv.c ../src/hvaf/ftmp/handler/ftmp_handler.c ../src/hvaf/ftmp/ftmp_common.c ../src/hvaf/ftmp/ftmp_sys.c ../src/hvaf/ftmp/ftmp_timer.c ../src/hvaf/test_manager/tm_fut.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1482089478/sys_clk_static.o ${OBJECTDIR}/_ext/148571690/sys_ports_static.o ${OBJECTDIR}/_ext/435813987/system_init.o ${OBJECTDIR}/_ext/435813987/system_interrupt.o ${OBJECTDIR}/_ext/435813987/system_exceptions.o ${OBJECTDIR}/_ext/435813987/system_tasks.o ${OBJECTDIR}/_ext/1360937237/main.o ${OBJECTDIR}/_ext/1264853842/app_test_drv_usart_basic_read_func.o ${OBJECTDIR}/_ext/1264853842/app_test_drv_usart_basic_write_func.o ${OBJECTDIR}/_ext/1360937237/app.o ${OBJECTDIR}/_ext/568269341/bsp_sys_init.o ${OBJECTDIR}/_ext/260586732/drv_usart.o ${OBJECTDIR}/_ext/260586732/drv_usart_read_write.o ${OBJECTDIR}/_ext/1271179505/sys_devcon.o ${OBJECTDIR}/_ext/1271179505/sys_devcon_pic32mx.o ${OBJECTDIR}/_ext/122796885/sys_int_pic32.o ${OBJECTDIR}/_ext/77319752/sys_ports.o ${OBJECTDIR}/_ext/1131018008/test_harness.o ${OBJECTDIR}/_ext/1101041029/data_class.o ${OBJECTDIR}/_ext/295896971/ftmp_drv_usart.o ${OBJECTDIR}/_ext/389309380/ftmp_drv.o ${OBJECTDIR}/_ext/163448178/ftmp_handler.o ${OBJECTDIR}/_ext/18323117/ftmp_common.o ${OBJECTDIR}/_ext/18323117/ftmp_sys.o ${OBJECTDIR}/_ext/18323117/ftmp_timer.o ${OBJECTDIR}/_ext/907219298/tm_fut.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1482089478/sys_clk_static.o.d ${OBJECTDIR}/_ext/148571690/sys_ports_static.o.d ${OBJECTDIR}/_ext/435813987/system_init.o.d ${OBJECTDIR}/_ext/435813987/system_interrupt.o.d ${OBJECTDIR}/_ext/435813987/system_exceptions.o.d ${OBJECTDIR}/_ext/435813987/system_tasks.o.d ${OBJECTDIR}/_ext/1360937237/main.o.d ${OBJECTDIR}/_ext/1264853842/app_test_drv_usart_basic_read_func.o.d ${OBJECTDIR}/_ext/1264853842/app_test_drv_usart_basic_write_func.o.d ${OBJECTDIR}/_ext/1360937237/app.o.d ${OBJECTDIR}/_ext/568269341/bsp_sys_init.o.d ${OBJECTDIR}/_ext/260586732/drv_usart.o.d ${OBJECTDIR}/_ext/260586732/drv_usart_read_write.o.d ${OBJECTDIR}/_ext/1271179505/sys_devcon.o.d ${OBJECTDIR}/_ext/1271179505/sys_devcon_pic32mx.o.d ${OBJECTDIR}/_ext/122796885/sys_int_pic32.o.d ${OBJECTDIR}/_ext/77319752/sys_ports.o.d ${OBJECTDIR}/_ext/1131018008/test_harness.o.d ${OBJECTDIR}/_ext/1101041029/data_class.o.d ${OBJECTDIR}/_ext/295896971/ftmp_drv_usart.o.d ${OBJECTDIR}/_ext/389309380/ftmp_drv.o.d ${OBJECTDIR}/_ext/163448178/ftmp_handler.o.d ${OBJECTDIR}/_ext/18323117/ftmp_common.o.d ${OBJECTDIR}/_ext/18323117/ftmp_sys.o.d ${OBJECTDIR}/_ext/18323117/ftmp_timer.o.d ${OBJECTDIR}/_ext/907219298/tm_fut.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1482089478/sys_clk_static.o ${OBJECTDIR}/_ext/148571690/sys_ports_static.o ${OBJECTDIR}/_ext/435813987/system_init.o ${OBJECTDIR}/_ext/435813987/system_interrupt.o ${OBJECTDIR}/_ext/435813987/system_exceptions.o ${OBJECTDIR}/_ext/435813987/system_tasks.o ${OBJECTDIR}/_ext/1360937237/main.o ${OBJECTDIR}/_ext/1264853842/app_test_drv_usart_basic_read_func.o ${OBJECTDIR}/_ext/1264853842/app_test_drv_usart_basic_write_func.o ${OBJECTDIR}/_ext/1360937237/app.o ${OBJECTDIR}/_ext/568269341/bsp_sys_init.o ${OBJECTDIR}/_ext/260586732/drv_usart.o ${OBJECTDIR}/_ext/260586732/drv_usart_read_write.o ${OBJECTDIR}/_ext/1271179505/sys_devcon.o ${OBJECTDIR}/_ext/1271179505/sys_devcon_pic32mx.o ${OBJECTDIR}/_ext/122796885/sys_int_pic32.o ${OBJECTDIR}/_ext/77319752/sys_ports.o ${OBJECTDIR}/_ext/1131018008/test_harness.o ${OBJECTDIR}/_ext/1101041029/data_class.o ${OBJECTDIR}/_ext/295896971/ftmp_drv_usart.o ${OBJECTDIR}/_ext/389309380/ftmp_drv.o ${OBJECTDIR}/_ext/163448178/ftmp_handler.o ${OBJECTDIR}/_ext/18323117/ftmp_common.o ${OBJECTDIR}/_ext/18323117/ftmp_sys.o ${OBJECTDIR}/_ext/18323117/ftmp_timer.o ${OBJECTDIR}/_ext/907219298/tm_fut.o

# Source Files
SOURCEFILES=../src/system_config/pic32mx/framework/system/clk/src/sys_clk_static.c ../src/system_config/pic32mx/framework/system/ports/src/sys_ports_static.c ../src/system_config/pic32mx/system_init.c ../src/system_config/pic32mx/system_interrupt.c ../src/system_config/pic32mx/system_exceptions.c ../src/system_config/pic32mx/system_tasks.c ../src/main.c ../src/test_app/app_test_drv_usart_basic_read_func.c ../src/test_app/app_test_drv_usart_basic_write_func.c ../src/app.c ../../../../bsp/pic32mx795_pim+e16/bsp_sys_init.c ../../../../framework/driver/usart/src/dynamic/drv_usart.c ../../../../framework/driver/usart/src/dynamic/drv_usart_read_write.c ../../../../framework/system/devcon/src/sys_devcon.c ../../../../framework/system/devcon/src/sys_devcon_pic32mx.c ../../../../framework/system/int/src/sys_int_pic32.c ../../../../framework/system/ports/src/sys_ports.c ../../../../framework/test/src/test_harness.c ../src/hvaf/data_class/data_class.c ../src/hvaf/ftmp/bus/ftmp_drv_usart/ftmp_drv_usart.c ../src/hvaf/ftmp/bus/ftmp_drv.c ../src/hvaf/ftmp/handler/ftmp_handler.c ../src/hvaf/ftmp/ftmp_common.c ../src/hvaf/ftmp/ftmp_sys.c ../src/hvaf/ftmp/ftmp_timer.c ../src/hvaf/test_manager/tm_fut.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-pic32mx.mk dist/${CND_CONF}/${IMAGE_TYPE}/test_usart_sample.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX795F512L
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1482089478/sys_clk_static.o: ../src/system_config/pic32mx/framework/system/clk/src/sys_clk_static.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1482089478" 
	@${RM} ${OBJECTDIR}/_ext/1482089478/sys_clk_static.o.d 
	@${RM} ${OBJECTDIR}/_ext/1482089478/sys_clk_static.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1482089478/sys_clk_static.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mx" -I"../src/pic32mx" -I"../../../../framework" -I"../src/system_config/pic32mx/framework" -I"../src/hvaf" -I"../src/hvaf/ftmp" -I"../src/hvaf/test_manager" -I"../../../../bsp/pic32mx795_pim+e16" -MMD -MF "${OBJECTDIR}/_ext/1482089478/sys_clk_static.o.d" -o ${OBJECTDIR}/_ext/1482089478/sys_clk_static.o ../src/system_config/pic32mx/framework/system/clk/src/sys_clk_static.c    -no-legacy-libc 
	
${OBJECTDIR}/_ext/148571690/sys_ports_static.o: ../src/system_config/pic32mx/framework/system/ports/src/sys_ports_static.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/148571690" 
	@${RM} ${OBJECTDIR}/_ext/148571690/sys_ports_static.o.d 
	@${RM} ${OBJECTDIR}/_ext/148571690/sys_ports_static.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/148571690/sys_ports_static.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mx" -I"../src/pic32mx" -I"../../../../framework" -I"../src/system_config/pic32mx/framework" -I"../src/hvaf" -I"../src/hvaf/ftmp" -I"../src/hvaf/test_manager" -I"../../../../bsp/pic32mx795_pim+e16" -MMD -MF "${OBJECTDIR}/_ext/148571690/sys_ports_static.o.d" -o ${OBJECTDIR}/_ext/148571690/sys_ports_static.o ../src/system_config/pic32mx/framework/system/ports/src/sys_ports_static.c    -no-legacy-libc 
	
${OBJECTDIR}/_ext/435813987/system_init.o: ../src/system_config/pic32mx/system_init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/435813987" 
	@${RM} ${OBJECTDIR}/_ext/435813987/system_init.o.d 
	@${RM} ${OBJECTDIR}/_ext/435813987/system_init.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/435813987/system_init.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mx" -I"../src/pic32mx" -I"../../../../framework" -I"../src/system_config/pic32mx/framework" -I"../src/hvaf" -I"../src/hvaf/ftmp" -I"../src/hvaf/test_manager" -I"../../../../bsp/pic32mx795_pim+e16" -MMD -MF "${OBJECTDIR}/_ext/435813987/system_init.o.d" -o ${OBJECTDIR}/_ext/435813987/system_init.o ../src/system_config/pic32mx/system_init.c    -no-legacy-libc 
	
${OBJECTDIR}/_ext/435813987/system_interrupt.o: ../src/system_config/pic32mx/system_interrupt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/435813987" 
	@${RM} ${OBJECTDIR}/_ext/435813987/system_interrupt.o.d 
	@${RM} ${OBJECTDIR}/_ext/435813987/system_interrupt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/435813987/system_interrupt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mx" -I"../src/pic32mx" -I"../../../../framework" -I"../src/system_config/pic32mx/framework" -I"../src/hvaf" -I"../src/hvaf/ftmp" -I"../src/hvaf/test_manager" -I"../../../../bsp/pic32mx795_pim+e16" -MMD -MF "${OBJECTDIR}/_ext/435813987/system_interrupt.o.d" -o ${OBJECTDIR}/_ext/435813987/system_interrupt.o ../src/system_config/pic32mx/system_interrupt.c    -no-legacy-libc 
	
${OBJECTDIR}/_ext/435813987/system_exceptions.o: ../src/system_config/pic32mx/system_exceptions.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/435813987" 
	@${RM} ${OBJECTDIR}/_ext/435813987/system_exceptions.o.d 
	@${RM} ${OBJECTDIR}/_ext/435813987/system_exceptions.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/435813987/system_exceptions.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mx" -I"../src/pic32mx" -I"../../../../framework" -I"../src/system_config/pic32mx/framework" -I"../src/hvaf" -I"../src/hvaf/ftmp" -I"../src/hvaf/test_manager" -I"../../../../bsp/pic32mx795_pim+e16" -MMD -MF "${OBJECTDIR}/_ext/435813987/system_exceptions.o.d" -o ${OBJECTDIR}/_ext/435813987/system_exceptions.o ../src/system_config/pic32mx/system_exceptions.c    -no-legacy-libc 
	
${OBJECTDIR}/_ext/435813987/system_tasks.o: ../src/system_config/pic32mx/system_tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/435813987" 
	@${RM} ${OBJECTDIR}/_ext/435813987/system_tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/435813987/system_tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/435813987/system_tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mx" -I"../src/pic32mx" -I"../../../../framework" -I"../src/system_config/pic32mx/framework" -I"../src/hvaf" -I"../src/hvaf/ftmp" -I"../src/hvaf/test_manager" -I"../../../../bsp/pic32mx795_pim+e16" -MMD -MF "${OBJECTDIR}/_ext/435813987/system_tasks.o.d" -o ${OBJECTDIR}/_ext/435813987/system_tasks.o ../src/system_config/pic32mx/system_tasks.c    -no-legacy-libc 
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mx" -I"../src/pic32mx" -I"../../../../framework" -I"../src/system_config/pic32mx/framework" -I"../src/hvaf" -I"../src/hvaf/ftmp" -I"../src/hvaf/test_manager" -I"../../../../bsp/pic32mx795_pim+e16" -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c    -no-legacy-libc 
	
${OBJECTDIR}/_ext/1264853842/app_test_drv_usart_basic_read_func.o: ../src/test_app/app_test_drv_usart_basic_read_func.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1264853842" 
	@${RM} ${OBJECTDIR}/_ext/1264853842/app_test_drv_usart_basic_read_func.o.d 
	@${RM} ${OBJECTDIR}/_ext/1264853842/app_test_drv_usart_basic_read_func.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1264853842/app_test_drv_usart_basic_read_func.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mx" -I"../src/pic32mx" -I"../../../../framework" -I"../src/system_config/pic32mx/framework" -I"../src/hvaf" -I"../src/hvaf/ftmp" -I"../src/hvaf/test_manager" -I"../../../../bsp/pic32mx795_pim+e16" -MMD -MF "${OBJECTDIR}/_ext/1264853842/app_test_drv_usart_basic_read_func.o.d" -o ${OBJECTDIR}/_ext/1264853842/app_test_drv_usart_basic_read_func.o ../src/test_app/app_test_drv_usart_basic_read_func.c    -no-legacy-libc 
	
${OBJECTDIR}/_ext/1264853842/app_test_drv_usart_basic_write_func.o: ../src/test_app/app_test_drv_usart_basic_write_func.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1264853842" 
	@${RM} ${OBJECTDIR}/_ext/1264853842/app_test_drv_usart_basic_write_func.o.d 
	@${RM} ${OBJECTDIR}/_ext/1264853842/app_test_drv_usart_basic_write_func.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1264853842/app_test_drv_usart_basic_write_func.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mx" -I"../src/pic32mx" -I"../../../../framework" -I"../src/system_config/pic32mx/framework" -I"../src/hvaf" -I"../src/hvaf/ftmp" -I"../src/hvaf/test_manager" -I"../../../../bsp/pic32mx795_pim+e16" -MMD -MF "${OBJECTDIR}/_ext/1264853842/app_test_drv_usart_basic_write_func.o.d" -o ${OBJECTDIR}/_ext/1264853842/app_test_drv_usart_basic_write_func.o ../src/test_app/app_test_drv_usart_basic_write_func.c    -no-legacy-libc 
	
${OBJECTDIR}/_ext/1360937237/app.o: ../src/app.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/app.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mx" -I"../src/pic32mx" -I"../../../../framework" -I"../src/system_config/pic32mx/framework" -I"../src/hvaf" -I"../src/hvaf/ftmp" -I"../src/hvaf/test_manager" -I"../../../../bsp/pic32mx795_pim+e16" -MMD -MF "${OBJECTDIR}/_ext/1360937237/app.o.d" -o ${OBJECTDIR}/_ext/1360937237/app.o ../src/app.c    -no-legacy-libc 
	
${OBJECTDIR}/_ext/568269341/bsp_sys_init.o: ../../../../bsp/pic32mx795_pim+e16/bsp_sys_init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/568269341" 
	@${RM} ${OBJECTDIR}/_ext/568269341/bsp_sys_init.o.d 
	@${RM} ${OBJECTDIR}/_ext/568269341/bsp_sys_init.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/568269341/bsp_sys_init.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mx" -I"../src/pic32mx" -I"../../../../framework" -I"../src/system_config/pic32mx/framework" -I"../src/hvaf" -I"../src/hvaf/ftmp" -I"../src/hvaf/test_manager" -I"../../../../bsp/pic32mx795_pim+e16" -MMD -MF "${OBJECTDIR}/_ext/568269341/bsp_sys_init.o.d" -o ${OBJECTDIR}/_ext/568269341/bsp_sys_init.o ../../../../bsp/pic32mx795_pim+e16/bsp_sys_init.c    -no-legacy-libc 
	
${OBJECTDIR}/_ext/260586732/drv_usart.o: ../../../../framework/driver/usart/src/dynamic/drv_usart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/260586732" 
	@${RM} ${OBJECTDIR}/_ext/260586732/drv_usart.o.d 
	@${RM} ${OBJECTDIR}/_ext/260586732/drv_usart.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/260586732/drv_usart.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mx" -I"../src/pic32mx" -I"../../../../framework" -I"../src/system_config/pic32mx/framework" -I"../src/hvaf" -I"../src/hvaf/ftmp" -I"../src/hvaf/test_manager" -I"../../../../bsp/pic32mx795_pim+e16" -MMD -MF "${OBJECTDIR}/_ext/260586732/drv_usart.o.d" -o ${OBJECTDIR}/_ext/260586732/drv_usart.o ../../../../framework/driver/usart/src/dynamic/drv_usart.c    -no-legacy-libc 
	
${OBJECTDIR}/_ext/260586732/drv_usart_read_write.o: ../../../../framework/driver/usart/src/dynamic/drv_usart_read_write.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/260586732" 
	@${RM} ${OBJECTDIR}/_ext/260586732/drv_usart_read_write.o.d 
	@${RM} ${OBJECTDIR}/_ext/260586732/drv_usart_read_write.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/260586732/drv_usart_read_write.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mx" -I"../src/pic32mx" -I"../../../../framework" -I"../src/system_config/pic32mx/framework" -I"../src/hvaf" -I"../src/hvaf/ftmp" -I"../src/hvaf/test_manager" -I"../../../../bsp/pic32mx795_pim+e16" -MMD -MF "${OBJECTDIR}/_ext/260586732/drv_usart_read_write.o.d" -o ${OBJECTDIR}/_ext/260586732/drv_usart_read_write.o ../../../../framework/driver/usart/src/dynamic/drv_usart_read_write.c    -no-legacy-libc 
	
${OBJECTDIR}/_ext/1271179505/sys_devcon.o: ../../../../framework/system/devcon/src/sys_devcon.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1271179505" 
	@${RM} ${OBJECTDIR}/_ext/1271179505/sys_devcon.o.d 
	@${RM} ${OBJECTDIR}/_ext/1271179505/sys_devcon.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1271179505/sys_devcon.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mx" -I"../src/pic32mx" -I"../../../../framework" -I"../src/system_config/pic32mx/framework" -I"../src/hvaf" -I"../src/hvaf/ftmp" -I"../src/hvaf/test_manager" -I"../../../../bsp/pic32mx795_pim+e16" -MMD -MF "${OBJECTDIR}/_ext/1271179505/sys_devcon.o.d" -o ${OBJECTDIR}/_ext/1271179505/sys_devcon.o ../../../../framework/system/devcon/src/sys_devcon.c    -no-legacy-libc 
	
${OBJECTDIR}/_ext/1271179505/sys_devcon_pic32mx.o: ../../../../framework/system/devcon/src/sys_devcon_pic32mx.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1271179505" 
	@${RM} ${OBJECTDIR}/_ext/1271179505/sys_devcon_pic32mx.o.d 
	@${RM} ${OBJECTDIR}/_ext/1271179505/sys_devcon_pic32mx.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1271179505/sys_devcon_pic32mx.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mx" -I"../src/pic32mx" -I"../../../../framework" -I"../src/system_config/pic32mx/framework" -I"../src/hvaf" -I"../src/hvaf/ftmp" -I"../src/hvaf/test_manager" -I"../../../../bsp/pic32mx795_pim+e16" -MMD -MF "${OBJECTDIR}/_ext/1271179505/sys_devcon_pic32mx.o.d" -o ${OBJECTDIR}/_ext/1271179505/sys_devcon_pic32mx.o ../../../../framework/system/devcon/src/sys_devcon_pic32mx.c    -no-legacy-libc 
	
${OBJECTDIR}/_ext/122796885/sys_int_pic32.o: ../../../../framework/system/int/src/sys_int_pic32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/122796885" 
	@${RM} ${OBJECTDIR}/_ext/122796885/sys_int_pic32.o.d 
	@${RM} ${OBJECTDIR}/_ext/122796885/sys_int_pic32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/122796885/sys_int_pic32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mx" -I"../src/pic32mx" -I"../../../../framework" -I"../src/system_config/pic32mx/framework" -I"../src/hvaf" -I"../src/hvaf/ftmp" -I"../src/hvaf/test_manager" -I"../../../../bsp/pic32mx795_pim+e16" -MMD -MF "${OBJECTDIR}/_ext/122796885/sys_int_pic32.o.d" -o ${OBJECTDIR}/_ext/122796885/sys_int_pic32.o ../../../../framework/system/int/src/sys_int_pic32.c    -no-legacy-libc 
	
${OBJECTDIR}/_ext/77319752/sys_ports.o: ../../../../framework/system/ports/src/sys_ports.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/77319752" 
	@${RM} ${OBJECTDIR}/_ext/77319752/sys_ports.o.d 
	@${RM} ${OBJECTDIR}/_ext/77319752/sys_ports.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/77319752/sys_ports.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mx" -I"../src/pic32mx" -I"../../../../framework" -I"../src/system_config/pic32mx/framework" -I"../src/hvaf" -I"../src/hvaf/ftmp" -I"../src/hvaf/test_manager" -I"../../../../bsp/pic32mx795_pim+e16" -MMD -MF "${OBJECTDIR}/_ext/77319752/sys_ports.o.d" -o ${OBJECTDIR}/_ext/77319752/sys_ports.o ../../../../framework/system/ports/src/sys_ports.c    -no-legacy-libc 
	
${OBJECTDIR}/_ext/1131018008/test_harness.o: ../../../../framework/test/src/test_harness.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1131018008" 
	@${RM} ${OBJECTDIR}/_ext/1131018008/test_harness.o.d 
	@${RM} ${OBJECTDIR}/_ext/1131018008/test_harness.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1131018008/test_harness.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mx" -I"../src/pic32mx" -I"../../../../framework" -I"../src/system_config/pic32mx/framework" -I"../src/hvaf" -I"../src/hvaf/ftmp" -I"../src/hvaf/test_manager" -I"../../../../bsp/pic32mx795_pim+e16" -MMD -MF "${OBJECTDIR}/_ext/1131018008/test_harness.o.d" -o ${OBJECTDIR}/_ext/1131018008/test_harness.o ../../../../framework/test/src/test_harness.c    -no-legacy-libc 
	
${OBJECTDIR}/_ext/1101041029/data_class.o: ../src/hvaf/data_class/data_class.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1101041029" 
	@${RM} ${OBJECTDIR}/_ext/1101041029/data_class.o.d 
	@${RM} ${OBJECTDIR}/_ext/1101041029/data_class.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1101041029/data_class.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mx" -I"../src/pic32mx" -I"../../../../framework" -I"../src/system_config/pic32mx/framework" -I"../src/hvaf" -I"../src/hvaf/ftmp" -I"../src/hvaf/test_manager" -I"../../../../bsp/pic32mx795_pim+e16" -MMD -MF "${OBJECTDIR}/_ext/1101041029/data_class.o.d" -o ${OBJECTDIR}/_ext/1101041029/data_class.o ../src/hvaf/data_class/data_class.c    -no-legacy-libc 
	
${OBJECTDIR}/_ext/295896971/ftmp_drv_usart.o: ../src/hvaf/ftmp/bus/ftmp_drv_usart/ftmp_drv_usart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/295896971" 
	@${RM} ${OBJECTDIR}/_ext/295896971/ftmp_drv_usart.o.d 
	@${RM} ${OBJECTDIR}/_ext/295896971/ftmp_drv_usart.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/295896971/ftmp_drv_usart.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mx" -I"../src/pic32mx" -I"../../../../framework" -I"../src/system_config/pic32mx/framework" -I"../src/hvaf" -I"../src/hvaf/ftmp" -I"../src/hvaf/test_manager" -I"../../../../bsp/pic32mx795_pim+e16" -MMD -MF "${OBJECTDIR}/_ext/295896971/ftmp_drv_usart.o.d" -o ${OBJECTDIR}/_ext/295896971/ftmp_drv_usart.o ../src/hvaf/ftmp/bus/ftmp_drv_usart/ftmp_drv_usart.c    -no-legacy-libc 
	
${OBJECTDIR}/_ext/389309380/ftmp_drv.o: ../src/hvaf/ftmp/bus/ftmp_drv.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/389309380" 
	@${RM} ${OBJECTDIR}/_ext/389309380/ftmp_drv.o.d 
	@${RM} ${OBJECTDIR}/_ext/389309380/ftmp_drv.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/389309380/ftmp_drv.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mx" -I"../src/pic32mx" -I"../../../../framework" -I"../src/system_config/pic32mx/framework" -I"../src/hvaf" -I"../src/hvaf/ftmp" -I"../src/hvaf/test_manager" -I"../../../../bsp/pic32mx795_pim+e16" -MMD -MF "${OBJECTDIR}/_ext/389309380/ftmp_drv.o.d" -o ${OBJECTDIR}/_ext/389309380/ftmp_drv.o ../src/hvaf/ftmp/bus/ftmp_drv.c    -no-legacy-libc 
	
${OBJECTDIR}/_ext/163448178/ftmp_handler.o: ../src/hvaf/ftmp/handler/ftmp_handler.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/163448178" 
	@${RM} ${OBJECTDIR}/_ext/163448178/ftmp_handler.o.d 
	@${RM} ${OBJECTDIR}/_ext/163448178/ftmp_handler.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/163448178/ftmp_handler.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mx" -I"../src/pic32mx" -I"../../../../framework" -I"../src/system_config/pic32mx/framework" -I"../src/hvaf" -I"../src/hvaf/ftmp" -I"../src/hvaf/test_manager" -I"../../../../bsp/pic32mx795_pim+e16" -MMD -MF "${OBJECTDIR}/_ext/163448178/ftmp_handler.o.d" -o ${OBJECTDIR}/_ext/163448178/ftmp_handler.o ../src/hvaf/ftmp/handler/ftmp_handler.c    -no-legacy-libc 
	
${OBJECTDIR}/_ext/18323117/ftmp_common.o: ../src/hvaf/ftmp/ftmp_common.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/18323117" 
	@${RM} ${OBJECTDIR}/_ext/18323117/ftmp_common.o.d 
	@${RM} ${OBJECTDIR}/_ext/18323117/ftmp_common.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/18323117/ftmp_common.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mx" -I"../src/pic32mx" -I"../../../../framework" -I"../src/system_config/pic32mx/framework" -I"../src/hvaf" -I"../src/hvaf/ftmp" -I"../src/hvaf/test_manager" -I"../../../../bsp/pic32mx795_pim+e16" -MMD -MF "${OBJECTDIR}/_ext/18323117/ftmp_common.o.d" -o ${OBJECTDIR}/_ext/18323117/ftmp_common.o ../src/hvaf/ftmp/ftmp_common.c    -no-legacy-libc 
	
${OBJECTDIR}/_ext/18323117/ftmp_sys.o: ../src/hvaf/ftmp/ftmp_sys.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/18323117" 
	@${RM} ${OBJECTDIR}/_ext/18323117/ftmp_sys.o.d 
	@${RM} ${OBJECTDIR}/_ext/18323117/ftmp_sys.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/18323117/ftmp_sys.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mx" -I"../src/pic32mx" -I"../../../../framework" -I"../src/system_config/pic32mx/framework" -I"../src/hvaf" -I"../src/hvaf/ftmp" -I"../src/hvaf/test_manager" -I"../../../../bsp/pic32mx795_pim+e16" -MMD -MF "${OBJECTDIR}/_ext/18323117/ftmp_sys.o.d" -o ${OBJECTDIR}/_ext/18323117/ftmp_sys.o ../src/hvaf/ftmp/ftmp_sys.c    -no-legacy-libc 
	
${OBJECTDIR}/_ext/18323117/ftmp_timer.o: ../src/hvaf/ftmp/ftmp_timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/18323117" 
	@${RM} ${OBJECTDIR}/_ext/18323117/ftmp_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/18323117/ftmp_timer.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/18323117/ftmp_timer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mx" -I"../src/pic32mx" -I"../../../../framework" -I"../src/system_config/pic32mx/framework" -I"../src/hvaf" -I"../src/hvaf/ftmp" -I"../src/hvaf/test_manager" -I"../../../../bsp/pic32mx795_pim+e16" -MMD -MF "${OBJECTDIR}/_ext/18323117/ftmp_timer.o.d" -o ${OBJECTDIR}/_ext/18323117/ftmp_timer.o ../src/hvaf/ftmp/ftmp_timer.c    -no-legacy-libc 
	
${OBJECTDIR}/_ext/907219298/tm_fut.o: ../src/hvaf/test_manager/tm_fut.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/907219298" 
	@${RM} ${OBJECTDIR}/_ext/907219298/tm_fut.o.d 
	@${RM} ${OBJECTDIR}/_ext/907219298/tm_fut.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/907219298/tm_fut.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mx" -I"../src/pic32mx" -I"../../../../framework" -I"../src/system_config/pic32mx/framework" -I"../src/hvaf" -I"../src/hvaf/ftmp" -I"../src/hvaf/test_manager" -I"../../../../bsp/pic32mx795_pim+e16" -MMD -MF "${OBJECTDIR}/_ext/907219298/tm_fut.o.d" -o ${OBJECTDIR}/_ext/907219298/tm_fut.o ../src/hvaf/test_manager/tm_fut.c    -no-legacy-libc 
	
else
${OBJECTDIR}/_ext/1482089478/sys_clk_static.o: ../src/system_config/pic32mx/framework/system/clk/src/sys_clk_static.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1482089478" 
	@${RM} ${OBJECTDIR}/_ext/1482089478/sys_clk_static.o.d 
	@${RM} ${OBJECTDIR}/_ext/1482089478/sys_clk_static.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1482089478/sys_clk_static.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mx" -I"../src/pic32mx" -I"../../../../framework" -I"../src/system_config/pic32mx/framework" -I"../src/hvaf" -I"../src/hvaf/ftmp" -I"../src/hvaf/test_manager" -I"../../../../bsp/pic32mx795_pim+e16" -MMD -MF "${OBJECTDIR}/_ext/1482089478/sys_clk_static.o.d" -o ${OBJECTDIR}/_ext/1482089478/sys_clk_static.o ../src/system_config/pic32mx/framework/system/clk/src/sys_clk_static.c    -no-legacy-libc 
	
${OBJECTDIR}/_ext/148571690/sys_ports_static.o: ../src/system_config/pic32mx/framework/system/ports/src/sys_ports_static.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/148571690" 
	@${RM} ${OBJECTDIR}/_ext/148571690/sys_ports_static.o.d 
	@${RM} ${OBJECTDIR}/_ext/148571690/sys_ports_static.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/148571690/sys_ports_static.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mx" -I"../src/pic32mx" -I"../../../../framework" -I"../src/system_config/pic32mx/framework" -I"../src/hvaf" -I"../src/hvaf/ftmp" -I"../src/hvaf/test_manager" -I"../../../../bsp/pic32mx795_pim+e16" -MMD -MF "${OBJECTDIR}/_ext/148571690/sys_ports_static.o.d" -o ${OBJECTDIR}/_ext/148571690/sys_ports_static.o ../src/system_config/pic32mx/framework/system/ports/src/sys_ports_static.c    -no-legacy-libc 
	
${OBJECTDIR}/_ext/435813987/system_init.o: ../src/system_config/pic32mx/system_init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/435813987" 
	@${RM} ${OBJECTDIR}/_ext/435813987/system_init.o.d 
	@${RM} ${OBJECTDIR}/_ext/435813987/system_init.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/435813987/system_init.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mx" -I"../src/pic32mx" -I"../../../../framework" -I"../src/system_config/pic32mx/framework" -I"../src/hvaf" -I"../src/hvaf/ftmp" -I"../src/hvaf/test_manager" -I"../../../../bsp/pic32mx795_pim+e16" -MMD -MF "${OBJECTDIR}/_ext/435813987/system_init.o.d" -o ${OBJECTDIR}/_ext/435813987/system_init.o ../src/system_config/pic32mx/system_init.c    -no-legacy-libc 
	
${OBJECTDIR}/_ext/435813987/system_interrupt.o: ../src/system_config/pic32mx/system_interrupt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/435813987" 
	@${RM} ${OBJECTDIR}/_ext/435813987/system_interrupt.o.d 
	@${RM} ${OBJECTDIR}/_ext/435813987/system_interrupt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/435813987/system_interrupt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mx" -I"../src/pic32mx" -I"../../../../framework" -I"../src/system_config/pic32mx/framework" -I"../src/hvaf" -I"../src/hvaf/ftmp" -I"../src/hvaf/test_manager" -I"../../../../bsp/pic32mx795_pim+e16" -MMD -MF "${OBJECTDIR}/_ext/435813987/system_interrupt.o.d" -o ${OBJECTDIR}/_ext/435813987/system_interrupt.o ../src/system_config/pic32mx/system_interrupt.c    -no-legacy-libc 
	
${OBJECTDIR}/_ext/435813987/system_exceptions.o: ../src/system_config/pic32mx/system_exceptions.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/435813987" 
	@${RM} ${OBJECTDIR}/_ext/435813987/system_exceptions.o.d 
	@${RM} ${OBJECTDIR}/_ext/435813987/system_exceptions.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/435813987/system_exceptions.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mx" -I"../src/pic32mx" -I"../../../../framework" -I"../src/system_config/pic32mx/framework" -I"../src/hvaf" -I"../src/hvaf/ftmp" -I"../src/hvaf/test_manager" -I"../../../../bsp/pic32mx795_pim+e16" -MMD -MF "${OBJECTDIR}/_ext/435813987/system_exceptions.o.d" -o ${OBJECTDIR}/_ext/435813987/system_exceptions.o ../src/system_config/pic32mx/system_exceptions.c    -no-legacy-libc 
	
${OBJECTDIR}/_ext/435813987/system_tasks.o: ../src/system_config/pic32mx/system_tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/435813987" 
	@${RM} ${OBJECTDIR}/_ext/435813987/system_tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/435813987/system_tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/435813987/system_tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mx" -I"../src/pic32mx" -I"../../../../framework" -I"../src/system_config/pic32mx/framework" -I"../src/hvaf" -I"../src/hvaf/ftmp" -I"../src/hvaf/test_manager" -I"../../../../bsp/pic32mx795_pim+e16" -MMD -MF "${OBJECTDIR}/_ext/435813987/system_tasks.o.d" -o ${OBJECTDIR}/_ext/435813987/system_tasks.o ../src/system_config/pic32mx/system_tasks.c    -no-legacy-libc 
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mx" -I"../src/pic32mx" -I"../../../../framework" -I"../src/system_config/pic32mx/framework" -I"../src/hvaf" -I"../src/hvaf/ftmp" -I"../src/hvaf/test_manager" -I"../../../../bsp/pic32mx795_pim+e16" -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c    -no-legacy-libc 
	
${OBJECTDIR}/_ext/1264853842/app_test_drv_usart_basic_read_func.o: ../src/test_app/app_test_drv_usart_basic_read_func.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1264853842" 
	@${RM} ${OBJECTDIR}/_ext/1264853842/app_test_drv_usart_basic_read_func.o.d 
	@${RM} ${OBJECTDIR}/_ext/1264853842/app_test_drv_usart_basic_read_func.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1264853842/app_test_drv_usart_basic_read_func.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mx" -I"../src/pic32mx" -I"../../../../framework" -I"../src/system_config/pic32mx/framework" -I"../src/hvaf" -I"../src/hvaf/ftmp" -I"../src/hvaf/test_manager" -I"../../../../bsp/pic32mx795_pim+e16" -MMD -MF "${OBJECTDIR}/_ext/1264853842/app_test_drv_usart_basic_read_func.o.d" -o ${OBJECTDIR}/_ext/1264853842/app_test_drv_usart_basic_read_func.o ../src/test_app/app_test_drv_usart_basic_read_func.c    -no-legacy-libc 
	
${OBJECTDIR}/_ext/1264853842/app_test_drv_usart_basic_write_func.o: ../src/test_app/app_test_drv_usart_basic_write_func.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1264853842" 
	@${RM} ${OBJECTDIR}/_ext/1264853842/app_test_drv_usart_basic_write_func.o.d 
	@${RM} ${OBJECTDIR}/_ext/1264853842/app_test_drv_usart_basic_write_func.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1264853842/app_test_drv_usart_basic_write_func.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mx" -I"../src/pic32mx" -I"../../../../framework" -I"../src/system_config/pic32mx/framework" -I"../src/hvaf" -I"../src/hvaf/ftmp" -I"../src/hvaf/test_manager" -I"../../../../bsp/pic32mx795_pim+e16" -MMD -MF "${OBJECTDIR}/_ext/1264853842/app_test_drv_usart_basic_write_func.o.d" -o ${OBJECTDIR}/_ext/1264853842/app_test_drv_usart_basic_write_func.o ../src/test_app/app_test_drv_usart_basic_write_func.c    -no-legacy-libc 
	
${OBJECTDIR}/_ext/1360937237/app.o: ../src/app.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/app.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mx" -I"../src/pic32mx" -I"../../../../framework" -I"../src/system_config/pic32mx/framework" -I"../src/hvaf" -I"../src/hvaf/ftmp" -I"../src/hvaf/test_manager" -I"../../../../bsp/pic32mx795_pim+e16" -MMD -MF "${OBJECTDIR}/_ext/1360937237/app.o.d" -o ${OBJECTDIR}/_ext/1360937237/app.o ../src/app.c    -no-legacy-libc 
	
${OBJECTDIR}/_ext/568269341/bsp_sys_init.o: ../../../../bsp/pic32mx795_pim+e16/bsp_sys_init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/568269341" 
	@${RM} ${OBJECTDIR}/_ext/568269341/bsp_sys_init.o.d 
	@${RM} ${OBJECTDIR}/_ext/568269341/bsp_sys_init.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/568269341/bsp_sys_init.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mx" -I"../src/pic32mx" -I"../../../../framework" -I"../src/system_config/pic32mx/framework" -I"../src/hvaf" -I"../src/hvaf/ftmp" -I"../src/hvaf/test_manager" -I"../../../../bsp/pic32mx795_pim+e16" -MMD -MF "${OBJECTDIR}/_ext/568269341/bsp_sys_init.o.d" -o ${OBJECTDIR}/_ext/568269341/bsp_sys_init.o ../../../../bsp/pic32mx795_pim+e16/bsp_sys_init.c    -no-legacy-libc 
	
${OBJECTDIR}/_ext/260586732/drv_usart.o: ../../../../framework/driver/usart/src/dynamic/drv_usart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/260586732" 
	@${RM} ${OBJECTDIR}/_ext/260586732/drv_usart.o.d 
	@${RM} ${OBJECTDIR}/_ext/260586732/drv_usart.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/260586732/drv_usart.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mx" -I"../src/pic32mx" -I"../../../../framework" -I"../src/system_config/pic32mx/framework" -I"../src/hvaf" -I"../src/hvaf/ftmp" -I"../src/hvaf/test_manager" -I"../../../../bsp/pic32mx795_pim+e16" -MMD -MF "${OBJECTDIR}/_ext/260586732/drv_usart.o.d" -o ${OBJECTDIR}/_ext/260586732/drv_usart.o ../../../../framework/driver/usart/src/dynamic/drv_usart.c    -no-legacy-libc 
	
${OBJECTDIR}/_ext/260586732/drv_usart_read_write.o: ../../../../framework/driver/usart/src/dynamic/drv_usart_read_write.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/260586732" 
	@${RM} ${OBJECTDIR}/_ext/260586732/drv_usart_read_write.o.d 
	@${RM} ${OBJECTDIR}/_ext/260586732/drv_usart_read_write.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/260586732/drv_usart_read_write.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mx" -I"../src/pic32mx" -I"../../../../framework" -I"../src/system_config/pic32mx/framework" -I"../src/hvaf" -I"../src/hvaf/ftmp" -I"../src/hvaf/test_manager" -I"../../../../bsp/pic32mx795_pim+e16" -MMD -MF "${OBJECTDIR}/_ext/260586732/drv_usart_read_write.o.d" -o ${OBJECTDIR}/_ext/260586732/drv_usart_read_write.o ../../../../framework/driver/usart/src/dynamic/drv_usart_read_write.c    -no-legacy-libc 
	
${OBJECTDIR}/_ext/1271179505/sys_devcon.o: ../../../../framework/system/devcon/src/sys_devcon.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1271179505" 
	@${RM} ${OBJECTDIR}/_ext/1271179505/sys_devcon.o.d 
	@${RM} ${OBJECTDIR}/_ext/1271179505/sys_devcon.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1271179505/sys_devcon.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mx" -I"../src/pic32mx" -I"../../../../framework" -I"../src/system_config/pic32mx/framework" -I"../src/hvaf" -I"../src/hvaf/ftmp" -I"../src/hvaf/test_manager" -I"../../../../bsp/pic32mx795_pim+e16" -MMD -MF "${OBJECTDIR}/_ext/1271179505/sys_devcon.o.d" -o ${OBJECTDIR}/_ext/1271179505/sys_devcon.o ../../../../framework/system/devcon/src/sys_devcon.c    -no-legacy-libc 
	
${OBJECTDIR}/_ext/1271179505/sys_devcon_pic32mx.o: ../../../../framework/system/devcon/src/sys_devcon_pic32mx.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1271179505" 
	@${RM} ${OBJECTDIR}/_ext/1271179505/sys_devcon_pic32mx.o.d 
	@${RM} ${OBJECTDIR}/_ext/1271179505/sys_devcon_pic32mx.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1271179505/sys_devcon_pic32mx.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mx" -I"../src/pic32mx" -I"../../../../framework" -I"../src/system_config/pic32mx/framework" -I"../src/hvaf" -I"../src/hvaf/ftmp" -I"../src/hvaf/test_manager" -I"../../../../bsp/pic32mx795_pim+e16" -MMD -MF "${OBJECTDIR}/_ext/1271179505/sys_devcon_pic32mx.o.d" -o ${OBJECTDIR}/_ext/1271179505/sys_devcon_pic32mx.o ../../../../framework/system/devcon/src/sys_devcon_pic32mx.c    -no-legacy-libc 
	
${OBJECTDIR}/_ext/122796885/sys_int_pic32.o: ../../../../framework/system/int/src/sys_int_pic32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/122796885" 
	@${RM} ${OBJECTDIR}/_ext/122796885/sys_int_pic32.o.d 
	@${RM} ${OBJECTDIR}/_ext/122796885/sys_int_pic32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/122796885/sys_int_pic32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mx" -I"../src/pic32mx" -I"../../../../framework" -I"../src/system_config/pic32mx/framework" -I"../src/hvaf" -I"../src/hvaf/ftmp" -I"../src/hvaf/test_manager" -I"../../../../bsp/pic32mx795_pim+e16" -MMD -MF "${OBJECTDIR}/_ext/122796885/sys_int_pic32.o.d" -o ${OBJECTDIR}/_ext/122796885/sys_int_pic32.o ../../../../framework/system/int/src/sys_int_pic32.c    -no-legacy-libc 
	
${OBJECTDIR}/_ext/77319752/sys_ports.o: ../../../../framework/system/ports/src/sys_ports.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/77319752" 
	@${RM} ${OBJECTDIR}/_ext/77319752/sys_ports.o.d 
	@${RM} ${OBJECTDIR}/_ext/77319752/sys_ports.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/77319752/sys_ports.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mx" -I"../src/pic32mx" -I"../../../../framework" -I"../src/system_config/pic32mx/framework" -I"../src/hvaf" -I"../src/hvaf/ftmp" -I"../src/hvaf/test_manager" -I"../../../../bsp/pic32mx795_pim+e16" -MMD -MF "${OBJECTDIR}/_ext/77319752/sys_ports.o.d" -o ${OBJECTDIR}/_ext/77319752/sys_ports.o ../../../../framework/system/ports/src/sys_ports.c    -no-legacy-libc 
	
${OBJECTDIR}/_ext/1131018008/test_harness.o: ../../../../framework/test/src/test_harness.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1131018008" 
	@${RM} ${OBJECTDIR}/_ext/1131018008/test_harness.o.d 
	@${RM} ${OBJECTDIR}/_ext/1131018008/test_harness.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1131018008/test_harness.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mx" -I"../src/pic32mx" -I"../../../../framework" -I"../src/system_config/pic32mx/framework" -I"../src/hvaf" -I"../src/hvaf/ftmp" -I"../src/hvaf/test_manager" -I"../../../../bsp/pic32mx795_pim+e16" -MMD -MF "${OBJECTDIR}/_ext/1131018008/test_harness.o.d" -o ${OBJECTDIR}/_ext/1131018008/test_harness.o ../../../../framework/test/src/test_harness.c    -no-legacy-libc 
	
${OBJECTDIR}/_ext/1101041029/data_class.o: ../src/hvaf/data_class/data_class.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1101041029" 
	@${RM} ${OBJECTDIR}/_ext/1101041029/data_class.o.d 
	@${RM} ${OBJECTDIR}/_ext/1101041029/data_class.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1101041029/data_class.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mx" -I"../src/pic32mx" -I"../../../../framework" -I"../src/system_config/pic32mx/framework" -I"../src/hvaf" -I"../src/hvaf/ftmp" -I"../src/hvaf/test_manager" -I"../../../../bsp/pic32mx795_pim+e16" -MMD -MF "${OBJECTDIR}/_ext/1101041029/data_class.o.d" -o ${OBJECTDIR}/_ext/1101041029/data_class.o ../src/hvaf/data_class/data_class.c    -no-legacy-libc 
	
${OBJECTDIR}/_ext/295896971/ftmp_drv_usart.o: ../src/hvaf/ftmp/bus/ftmp_drv_usart/ftmp_drv_usart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/295896971" 
	@${RM} ${OBJECTDIR}/_ext/295896971/ftmp_drv_usart.o.d 
	@${RM} ${OBJECTDIR}/_ext/295896971/ftmp_drv_usart.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/295896971/ftmp_drv_usart.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mx" -I"../src/pic32mx" -I"../../../../framework" -I"../src/system_config/pic32mx/framework" -I"../src/hvaf" -I"../src/hvaf/ftmp" -I"../src/hvaf/test_manager" -I"../../../../bsp/pic32mx795_pim+e16" -MMD -MF "${OBJECTDIR}/_ext/295896971/ftmp_drv_usart.o.d" -o ${OBJECTDIR}/_ext/295896971/ftmp_drv_usart.o ../src/hvaf/ftmp/bus/ftmp_drv_usart/ftmp_drv_usart.c    -no-legacy-libc 
	
${OBJECTDIR}/_ext/389309380/ftmp_drv.o: ../src/hvaf/ftmp/bus/ftmp_drv.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/389309380" 
	@${RM} ${OBJECTDIR}/_ext/389309380/ftmp_drv.o.d 
	@${RM} ${OBJECTDIR}/_ext/389309380/ftmp_drv.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/389309380/ftmp_drv.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mx" -I"../src/pic32mx" -I"../../../../framework" -I"../src/system_config/pic32mx/framework" -I"../src/hvaf" -I"../src/hvaf/ftmp" -I"../src/hvaf/test_manager" -I"../../../../bsp/pic32mx795_pim+e16" -MMD -MF "${OBJECTDIR}/_ext/389309380/ftmp_drv.o.d" -o ${OBJECTDIR}/_ext/389309380/ftmp_drv.o ../src/hvaf/ftmp/bus/ftmp_drv.c    -no-legacy-libc 
	
${OBJECTDIR}/_ext/163448178/ftmp_handler.o: ../src/hvaf/ftmp/handler/ftmp_handler.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/163448178" 
	@${RM} ${OBJECTDIR}/_ext/163448178/ftmp_handler.o.d 
	@${RM} ${OBJECTDIR}/_ext/163448178/ftmp_handler.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/163448178/ftmp_handler.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mx" -I"../src/pic32mx" -I"../../../../framework" -I"../src/system_config/pic32mx/framework" -I"../src/hvaf" -I"../src/hvaf/ftmp" -I"../src/hvaf/test_manager" -I"../../../../bsp/pic32mx795_pim+e16" -MMD -MF "${OBJECTDIR}/_ext/163448178/ftmp_handler.o.d" -o ${OBJECTDIR}/_ext/163448178/ftmp_handler.o ../src/hvaf/ftmp/handler/ftmp_handler.c    -no-legacy-libc 
	
${OBJECTDIR}/_ext/18323117/ftmp_common.o: ../src/hvaf/ftmp/ftmp_common.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/18323117" 
	@${RM} ${OBJECTDIR}/_ext/18323117/ftmp_common.o.d 
	@${RM} ${OBJECTDIR}/_ext/18323117/ftmp_common.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/18323117/ftmp_common.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mx" -I"../src/pic32mx" -I"../../../../framework" -I"../src/system_config/pic32mx/framework" -I"../src/hvaf" -I"../src/hvaf/ftmp" -I"../src/hvaf/test_manager" -I"../../../../bsp/pic32mx795_pim+e16" -MMD -MF "${OBJECTDIR}/_ext/18323117/ftmp_common.o.d" -o ${OBJECTDIR}/_ext/18323117/ftmp_common.o ../src/hvaf/ftmp/ftmp_common.c    -no-legacy-libc 
	
${OBJECTDIR}/_ext/18323117/ftmp_sys.o: ../src/hvaf/ftmp/ftmp_sys.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/18323117" 
	@${RM} ${OBJECTDIR}/_ext/18323117/ftmp_sys.o.d 
	@${RM} ${OBJECTDIR}/_ext/18323117/ftmp_sys.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/18323117/ftmp_sys.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mx" -I"../src/pic32mx" -I"../../../../framework" -I"../src/system_config/pic32mx/framework" -I"../src/hvaf" -I"../src/hvaf/ftmp" -I"../src/hvaf/test_manager" -I"../../../../bsp/pic32mx795_pim+e16" -MMD -MF "${OBJECTDIR}/_ext/18323117/ftmp_sys.o.d" -o ${OBJECTDIR}/_ext/18323117/ftmp_sys.o ../src/hvaf/ftmp/ftmp_sys.c    -no-legacy-libc 
	
${OBJECTDIR}/_ext/18323117/ftmp_timer.o: ../src/hvaf/ftmp/ftmp_timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/18323117" 
	@${RM} ${OBJECTDIR}/_ext/18323117/ftmp_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/18323117/ftmp_timer.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/18323117/ftmp_timer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mx" -I"../src/pic32mx" -I"../../../../framework" -I"../src/system_config/pic32mx/framework" -I"../src/hvaf" -I"../src/hvaf/ftmp" -I"../src/hvaf/test_manager" -I"../../../../bsp/pic32mx795_pim+e16" -MMD -MF "${OBJECTDIR}/_ext/18323117/ftmp_timer.o.d" -o ${OBJECTDIR}/_ext/18323117/ftmp_timer.o ../src/hvaf/ftmp/ftmp_timer.c    -no-legacy-libc 
	
${OBJECTDIR}/_ext/907219298/tm_fut.o: ../src/hvaf/test_manager/tm_fut.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/907219298" 
	@${RM} ${OBJECTDIR}/_ext/907219298/tm_fut.o.d 
	@${RM} ${OBJECTDIR}/_ext/907219298/tm_fut.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/907219298/tm_fut.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mx" -I"../src/pic32mx" -I"../../../../framework" -I"../src/system_config/pic32mx/framework" -I"../src/hvaf" -I"../src/hvaf/ftmp" -I"../src/hvaf/test_manager" -I"../../../../bsp/pic32mx795_pim+e16" -MMD -MF "${OBJECTDIR}/_ext/907219298/tm_fut.o.d" -o ${OBJECTDIR}/_ext/907219298/tm_fut.o ../src/hvaf/test_manager/tm_fut.c    -no-legacy-libc 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/test_usart_sample.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../../../../bin/framework/peripheral/PIC32MX795F512L_peripherals.a  
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mdebugger -D__MPLAB_DEBUGGER_PIC32MXSK=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/test_usart_sample.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ..\..\..\..\bin\framework\peripheral\PIC32MX795F512L_peripherals.a      -no-legacy-libc      -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PIC32MXSK=1,--defsym=_min_heap_size=0,--gc-sections,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/test_usart_sample.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../../../../bin/framework/peripheral/PIC32MX795F512L_peripherals.a 
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/test_usart_sample.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ..\..\..\..\bin\framework\peripheral\PIC32MX795F512L_peripherals.a      -no-legacy-libc  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=0,--gc-sections,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/test_usart_sample.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/pic32mx
	${RM} -r dist/pic32mx

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
