set(modules DuneBoost.cmake
  DuneCommonMacros.cmake
  DuneCxaDemangle.cmake
  DuneDoc.cmake
  DuneDoxygen.cmake
  DuneMacros.cmake
  DuneMPI.cmake
  DunePkgConfig.cmake
  DuneStreams.cmake
  DuneTestMacros.cmake
  DuneTests.cmake
  FindBoostFusion.cmake
  FindCXX11Features.cmake
  FindGMP.cmake
  FindInkscape.cmake
  FindMETIS.cmake
  FindMProtect.cmake
  FindParMETIS.cmake
  FindSharedPtr.cmake
  LanguageSupport.cmake
  UseLATEX.cmake)
install(FILES ${modules} DESTINATION ${DUNE_INSTALL_MODULEDIR})
