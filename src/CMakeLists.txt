cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project (libJetScape)

#for MacOSX
cmake_policy(SET CMP0042 NEW)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "./lib")

# framework
FILE(GLOB frameworksources framework/*.cc)
set (SOURCES  ${SOURCES}  ${frameworksources} )

## Take care of options
## Note that cmake NOT needs the "" to deal with empty variables
# if(NOT "${ZLIB_FOUND}")
#   list (REMOVE_ITEM SOURCES ${CMAKE_SOURCE_DIR}/src/framework/JetScapeWriterAsciiGZ.cc)
# endif()

if(NOT "${HEPMC_FOUND}")
  list (REMOVE_ITEM SOURCES ${CMAKE_SOURCE_DIR}/src/framework/JetScapeWriterHepMC.cc)
endif()

#initialstate
FILE(GLOB initialstatesources initialstate/*.cc)
set (SOURCES  ${SOURCES}  ${initialstatesources} )

#trento needs data tables
#file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/data_table)
#file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/initialstate/data_table/
#  DESTINATION ${CMAKE_BINARY_DIR}/data_table
#  )

#pre-equilibrium
FILE(GLOB preeqsources preequilibrium/*.cc)
set (SOURCES  ${SOURCES}  ${preeqsources} )
## Take care of options
if(NOT "${freestream}")
  list (REMOVE_ITEM SOURCES ${CMAKE_SOURCE_DIR}/src/preequilibrium/FreestreamMilneWrapper.cc)
endif()
if(NOT "${ktiso}")
  list (REMOVE_ITEM SOURCES ${CMAKE_SOURCE_DIR}/src/preequilibrium/KTIsoWrapper.cc)
endif()

#hydro
FILE(GLOB hydrosources hydro/*.cc)
set (SOURCES  ${SOURCES}  ${hydrosources} )
## Take care of options
if(NOT "${music}")
  list (REMOVE_ITEM SOURCES ${CMAKE_SOURCE_DIR}/src/hydro/MusicWrapper.cc)
endif()

#afterburner
FILE(GLOB afterburnersources afterburner/*.cc)
set (SOURCES  ${SOURCES}  ${afterburnersources} )
## Take care of options
if(NOT "${smash}")
  list (REMOVE_ITEM SOURCES ${CMAKE_SOURCE_DIR}/src/afterburner/SmashWrapper.cc)
endif()

#jet
FILE(GLOB jetsources jet/*.cc)
set (SOURCES  ${SOURCES}  ${jetsources} )

#hadronization
FILE(GLOB hadrosources hadronization/*.cc)
set (SOURCES  ${SOURCES}  ${hadrosources} )

## Take care of options
if(NOT "${iSS}")
  list (REMOVE_ITEM SOURCES ${CMAKE_SOURCE_DIR}/src/hadronization/iSpectraSamplerWrapper.cc)
endif()

if(NOT "${iS3D}")
  list (REMOVE_ITEM SOURCES ${CMAKE_SOURCE_DIR}/src/hadronization/iS3DWrapper.cc)
endif()

#reader
FILE(GLOB readersources reader/*.cc)
set (SOURCES  ${SOURCES}  ${readersources} )


#######################################

add_library(JetScape SHARED ${SOURCES})
target_link_libraries(JetScape JetScapeThird GTL ${PYTHIA8_LIBRARIES} libtrento ${Boost_LIBRARIES}  ${GSL_LIBRARIES})

if (${ROOT_FOUND})
  target_link_libraries(JetScape ${ROOT_LIBRARIES})
endif()

if (${HDF5_FOUND})
  target_link_libraries (JetScape hydroFromFile ${_hdf5_libs})
endif()

if ( ${HEPMC_FOUND} )
  target_link_libraries (JetScape -L${HEPMC_LIB_DIR} -lHepMC )
endif()

if ( music )
  target_link_libraries (JetScape music_lib )
endif()

if ( iSS )
  target_link_libraries (JetScape iSS_lib )
endif()


if ( iS3D )
  target_link_libraries (JetScape iS3D_lib )
endif()


if ( smash )
  # "-lubsan -lasan") # - in case of problems with address sanitizer
  target_link_libraries (JetScape ${SMASH_LIBRARIES})
endif()

# -------------------------------------------------------------------------
