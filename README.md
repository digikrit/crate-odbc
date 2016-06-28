# crate-odbc

## [Crate](http://crate.io) ODBC Connector (EXPERIMENTAL, NOT COMPLETE)

ODBC is a C API that provides a standard way of communicating with anything that accepts SQL-like input; the ODBC Driver lets you communicate with Crate via this standard. The high-level goal is to be able to communicate with Crate from various ODBC clients like MS Query, MS Excel, and Tableau. It aims to provide a way to run sql-odbc based applications on top of Crate.

This driver is written in the C Programming Language.

## Current Status

* Only tested on linux (centos 6.5)
* The only error handling in place is a "catch and log" strategy
* Many functions are not implemented, the driver does *not* meet the "Core" level of [ODBC conformance](odbc-conformance.md)
* Most queries will work as expected
* The driver is single-threaded

## Goals

* Full ODBC 3.51 conformance
* Full support on Windows/Mac/Linux

## Development Environment Requirements
* Emacs with C mode
* Make
* ODBC, Curl and Jansson libraries

## Compile Driver & Run Examples 
$make
