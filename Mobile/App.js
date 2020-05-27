/**
 * Sample React Native App
 * https://github.com/facebook/react-native
 *
 * @format
 * @flow
 */

import React, {useState, useEffect} from 'react';
import {KeyboardAvoidingView, View, Text, Image, StatusBar} from 'react-native';

import styles from './style';

import firebase from 'firebase';

export default function App() {
  //let [inputSetPoint, inputsetSetPoint] = useState('');
  let [SetPoint, setSetPoint] = useState('');
  let [flow, setFlow] = useState('');
  let [rotation, setRotation] = useState('');
  let [opening, setOpening] = useState('');
  let [kd, setKd] = useState('');
  let [ki, setKi] = useState('');
  let [kp, setKp] = useState('');

  function loadDates() {
    firebase
      .database()
      .ref()
      .child('stand/')
      .once('value')
      .then(snapshot => {
        let data = snapshot.val();
        setFlow(data.flow.flow);
        setOpening(data.opening.opening);
        setRotation(data.rotation.rotation);
        setSetPoint(data.SetPoint.SetPoint);
        setKp(data.Kp.Kp);
        setKi(data.Ki.Ki);
        setKd(data.Kd.Kd);
      });
  }

  firebase
    .database()
    .ref()
    .child('stand/')
    .on('child_changed', snapshot => {
      let data = snapshot.val();
      if (snapshot.key === 'flow') {
        setFlow(data.flow);
      } else if (snapshot.key === 'opening') {
        setOpening(data.opening);
      } else if (snapshot.key === 'rotation') {
        setRotation(data.rotation);
      } else if (snapshot.key === 'SetPoint') {
        setSetPoint(data.SetPoint);
      } else if (snapshot.key === 'Kp') {
        setKp(data.Kp);
      } else if (snapshot.key === 'Ki') {
        setKi(data.Ki);
      } else if (snapshot.key === 'Kd') {
        setKd(data.Kd);
      }
    });

  useEffect(() => {
    loadDates();
  }, []);

  return (
    <>
      <StatusBar barStyle="dark-content" />
      <View style={styles.container}>
        <KeyboardAvoidingView behavior="padding" style={styles.input2}>
          <Text style={styles.title}>Bancada de multiprocessos</Text>
          <Text style={styles.title}>(Malha de Vazão)</Text>
          <View style={styles.blocos2}>
            <Text style={styles.blocos}>Variáveis de processo</Text>
          </View>
          <View style={styles.quadrado}>
            <Text style={styles.texts}>Vazão (l/h): {flow}</Text>
            <Text style={styles.texts}>SetPoint (l/h): {SetPoint}</Text>
            <Text style={styles.texts}>Status da bomba (Rpm): {rotation}</Text>
            <Text style={styles.texts}>Abertura da válvula (%): {opening}</Text>
          </View>
          <View style={styles.blocos2}>
            <Text style={styles.blocos}>Ganho do controlador</Text>
          </View>
          <View style={styles.quadrado2}>
            <Text style={styles.texts}>Kp: {kp}</Text>
            <Text style={styles.texts}>Ki: {ki}</Text>
            <Text style={styles.texts}>Kd: {kd}</Text>
          </View>
          <Image style={styles.modbus} source={require('./modbus.png')} />
        </KeyboardAvoidingView>
      </View>
    </>
  );
}

//export default App;
