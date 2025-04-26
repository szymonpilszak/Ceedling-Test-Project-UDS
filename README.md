***UDS 0x22 Service Example Project***
Overview
This project demonstrates unit testing for an embedded C implementation of the UDS (Unified Diagnostic Services) 0x22 ReadDataByIdentifier service using the Ceedling test framework.

***Key Features***
  -  Unit tests for UDS 0x22 service handler
  -  Example implementation of ReadDataByIdentifier service
  -  Ceedling test framework configuration
  -  Mocking of hardware dependencies
  -  Designed for embedded systems

***Future Plans***
  -  Add more UDS services (0x10, 0x27, etc.)
  -  Implement integration testing
  -  Add continuous integration pipeline

***Requirements***
  -  Ruby (for Ceedling)
  -  GCC or other C cross-compiler
  -  Unity test framework (included with Ceedling)

***Getting Started***
  -  Install Ceedling: gem install ceedling
  -  Build and run tests: ceedling test:all
