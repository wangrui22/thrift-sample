package com.example.thriftserver;

import org.apache.thrift.TProcessorFactory;
import org.apache.thrift.protocol.TCompactProtocol;
import org.apache.thrift.protocol.TProtocolFactory;
import org.apache.thrift.server.TThreadedSelectorServer;
import org.apache.thrift.transport.*;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;


import org.apache.thrift.server.TServer;
import org.apache.thrift.server.TServer.Args;
import org.apache.thrift.server.TSimpleServer;
import org.apache.thrift.server.TThreadPoolServer;
import org.apache.thrift.transport.TSSLTransportFactory.TSSLTransportParameters;
import org.apache.thrift.transport.TTransportException;

import tutorial.*;
import shared.*;

import java.util.HashMap;

@SpringBootApplication
public class ThriftserverApplication {


	// public static void main(String[] args) {
	// 	SpringApplication.run(ThriftserverApplication.class, args);
	// }

  public static CalculatorHandler handler;

  public static Calculator.Processor processor;

  public static void main(String [] args) {
    try {
      handler = new CalculatorHandler();
      processor = new Calculator.Processor(handler);

//      Runnable simple = new Runnable() {
//        public void run() {
//          simple(processor);
//        }
//      };
       Runnable ts = new Runnable() {
         public void run() {
           ts(processor);
         }
       };

      //new Thread(simple).start();
      new Thread(ts).start();
    } catch (Exception x) {
      x.printStackTrace();
    }
  }

  public static void simple(Calculator.Processor processor) {
    try {
      TServerTransport serverTransport = new TServerSocket(9090);
      TServer server = new TSimpleServer(new Args(serverTransport).processor(processor));

      // Use this for a multithreaded server
      // TServer server = new TThreadPoolServer(new TThreadPoolServer.Args(serverTransport).processor(processor));

      System.out.println("Starting the simple server...");
      server.serve();
    } catch (Exception e) {
      e.printStackTrace();
    }
  }

  public static void ts(tutorial.Calculator.Processor processor) {
    try{
      TNonblockingServerSocket serverTransport = new TNonblockingServerSocket(9090);
      TProtocolFactory propFactory = new TCompactProtocol.Factory();
      TThreadedSelectorServer.Args args = new TThreadedSelectorServer.Args(serverTransport);
      args.processor(processor);
      args.selectorThreads(5);
      args.workerThreads(10);
      args.acceptQueueSizePerThread(7);
      args.protocolFactory(propFactory);
      TServer server = new TThreadedSelectorServer(args);
      server.serve();
    } catch (TTransportException e) {
      e.printStackTrace();
    }
  }

//  public static void secure(Calculator.Processor processor) {
//    try {
//      /*
//       * Use TSSLTransportParameters to setup the required SSL parameters. In this example
//       * we are setting the keystore and the keystore password. Other things like algorithms,
//       * cipher suites, client auth etc can be set.
//       */
//      TSSLTransportParameters params = new TSSLTransportParameters();
//      // The Keystore contains the private key
//      params.setKeyStore("../../lib/java/test/.keystore", "thrift", null, null);
//
//      /*
//       * Use any of the TSSLTransportFactory to get a server transport with the appropriate
//       * SSL configuration. You can use the default settings if properties are set in the command line.
//       * Ex: -Djavax.net.ssl.keyStore=.keystore and -Djavax.net.ssl.keyStorePassword=thrift
//       *
//       * Note: You need not explicitly call open(). The underlying server socket is bound on return
//       * from the factory class.
//       */
//      TServerTransport serverTransport = TSSLTransportFactory.getServerSocket(9091, 0, null, params);
//      TServer server = new TSimpleServer(new Args(serverTransport).processor(processor));
//
//      // Use this for a multi threaded server
//      // TServer server = new TThreadPoolServer(new TThreadPoolServer.Args(serverTransport).processor(processor));
//
//      System.out.println("Starting the secure server...");
//      server.serve();
//    } catch (Exception e) {
//      e.printStackTrace();
//    }
//  }

}
