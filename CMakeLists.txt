cmake_minimum_required(VERSION 3.5)
project (epics_fetcher)

set (CMAKE_CXX_STANDARD 11)

set(tgt epics_fetcher)

include_directories(
    "/opt/epics/modules/pvaClientCPP/include" 
    "/opt/epics/modules/pvDataCPP/include"
    "/opt/epics/modules/pvAccessCPP/include"
    "/opt/epics/modules/normativeTypesCPP/include"
    "/opt/epics/bases/base-3.15.2/include"
    "/opt/epics/bases/base-3.15.2/include/compiler/gcc"
    "/opt/epics/bases/base-3.15.2/include/os/Linux"
)

# link_directories(
#     /opt/epics/modules/pvaClientCPP/lib/linux-x86_64
# )

add_executable(epics_fetcher epics_fetcher.cpp)

find_library(PVA_CLIENT pvaClient HINTS /opt/epics/modules/pvaClientCPP/lib/linux-x86_64)
find_library(PV_DATA pvData HINTS /opt/epics/modules/pvDataCPP/lib/linux-x86_64)
find_library(CA ca HINTS /opt/epics/bases/base-3.15.2/lib/linux-x86_64)

target_link_libraries(epics_fetcher ${PVA_CLIENT})
target_link_libraries(epics_fetcher ${CA})
target_link_libraries(epics_fetcher ${PV_DATA})

