  <h1 align="center"> UDS 0x22 Service Example TEST Project</h1>

***Build Status***


![Build Status](https://github.com/szymonpilszak/UDS-Diagnostic-Service-Demo-Ceedling-C/actions/workflows/ci.yml/badge.svg)



***COVERAGE REPORTS***

+  https://szymonpilszak.github.io/Ceedling-Test-Project-UDS/coverage_report.html

+  https://szymonpilszak.github.io/Ceedling-Test-Project-UDS/coverage_report.functions.html


Overview

This project demonstrates unit testing for an embedded C implementation of the UDS (Unified Diagnostic Services) 0x22 ReadDataByIdentifier service using the Ceedling test framework.


***Key Features***
  -  Unit tests for UDS 0x22 service handler
  -  Example implementation of ReadDataByIdentifier service
  -  Ceedling test framework configuration
  -  Mocking of hardware dependencies (e.g., communication layers)
  -  Designed for embedded systems (AUTOSAR-like structure)
  - Generation of code coverage reports (GCOV + GCOVR)

***Future Plans***
  -  Add more UDS services (0x10, 0x27, etc.)
  -  Implement integration testing
  -  Add continuous integration pipeline

***Requirements***
- **Ruby** (for Ceedling) — [Download Ruby](https://rubyinstaller.org/)
- **Ceedling** — Unit test framework based on Unity & CMock
- **Python 3** (for gcovr code coverage reporting)
- **GCC** ( v13.3 or compatible C compiler like MinGW-w64 on Windows)
- **gcovr** (Python tool for code coverage visualization)

***Getting Started***
  -  Ensure you have Ruby installed (required for Ceedling)
  -  Ensure you have gcc installed (v13.3)
  -  Install Ceedling: gem install ceedling
  -  Install Python and gcovr
  -  Clone the Repository : git clone https://github.com/szymonpilszak/UDS-Diagnostic-Service-Demo-Ceedling-C.git
  -  Build and run tests: ceedling test:all
