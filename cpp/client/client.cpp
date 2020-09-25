/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements. See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership. The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License. You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied. See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#include <iostream>

#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>
#include <thrift/protocol/TCompactProtocol.h>

#include "../gen-cpp/Calculator.h"

using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

using namespace tutorial;
using namespace shared;

// int main() {
//   std::shared_ptr<TTransport> socket(new TSocket("localhost", 9090));
//   // std::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
//   // std::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
//   std::shared_ptr<TTransport> transport(new TFramedTransport(socket));
//   std::shared_ptr<TProtocol> protocol(new TCompactProtocol(transport));
//   CalculatorClient client(protocol);

//   try {
//     transport->open();

//     client.ping();
//     cout << "ping()" << endl;

//     cout << "1 + 1 = " << client.add(1, 1) << endl;

//     Work work;
//     work.op = Operation::DIVIDE;
//     work.num1 = 1;
//     work.num2 = 0;

//     try {
//       client.calculate(1, work);
//       cout << "Whoa? We can divide by zero!" << endl;
//     } catch (InvalidOperation& io) {
//       cout << "InvalidOperation: " << io.why << endl;
//       // or using generated operator<<: cout << io << endl;
//       // or by using std::exception native method what(): cout << io.what() << endl;
//     }

//     work.op = Operation::SUBTRACT;
//     work.num1 = 15;
//     work.num2 = 10;
//     int32_t diff = client.calculate(1, work);
//     cout << "15 - 10 = " << diff << endl;

//     // Note that C++ uses return by reference for complex types to avoid
//     // costly copy construction
//     SharedStruct ss;
//     client.getStruct(ss, 1);
//     cout << "Received log: " << ss << endl;

//     exit(0);

//     //transport->close();
//   } catch (TException& tx) {
//     cout << "ERROR: " << tx.what() << endl;
//   }
// }


int main() {
  std::vector<std::shared_ptr<TTransport>>t0;
  std::vector<std::shared_ptr<TTransport>> t1;
  std::vector<std::shared_ptr<TProtocol>> t2;
  std::vector<std::shared_ptr<CalculatorClient>> t3;

  for (int i=0; i<10; ++i) {
    std::shared_ptr<TTransport> socket(new TSocket("localhost", 9090));
    // std::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
    // std::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
    std::shared_ptr<TTransport> transport(new TFramedTransport(socket));
    std::shared_ptr<TProtocol> protocol(new TCompactProtocol(transport));
    std::shared_ptr<CalculatorClient> client(new CalculatorClient(protocol));

    t0.push_back(socket);
    t1.push_back(transport);
    t2.push_back(protocol);
    t3.push_back(client);
     

    try {
      transport->open();

      client->ping();
      cout << "ping()" << endl;

      cout << "1 + 1 = " << client->add(1, 1) << endl;

      Work work;
      work.op = Operation::DIVIDE;
      work.num1 = 1;
      work.num2 = 0;

      try {
        client->calculate(1, work);
        cout << "Whoa? We can divide by zero!" << endl;
      } catch (InvalidOperation& io) {
        cout << "InvalidOperation: " << io.why << endl;
        // or using generated operator<<: cout << io << endl;
        // or by using std::exception native method what(): cout << io.what() << endl;
      }

      work.op = Operation::SUBTRACT;
      work.num1 = 15;
      work.num2 = 10;
      int32_t diff = client->calculate(1, work);
      cout << "15 - 10 = " << diff << endl;

      // Note that C++ uses return by reference for complex types to avoid
      // costly copy construction
      SharedStruct ss;
      client->getStruct(ss, 1);
      cout << "Received log: " << ss << endl;

      //transport->close();
    } catch (TException& tx) {
      cout << "ERROR: " << tx.what() << endl;
    }
  }

  exit(0);
  
}
