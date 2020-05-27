//import React from 'react';
import {StyleSheet, Dimensions} from 'react-native';

const styles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: '#ffff',
  },
  quadrado: {
    height: 250,
    borderWidth: 1,
    width: 345,
    alignSelf: 'center',
    borderTopEndRadius: 2,
    borderTopStartRadius: 2,
  },
  quadrado2: {
    height: 200,
    borderWidth: 1,
    width: 345,
    alignSelf: 'center',
    borderTopEndRadius: 2,
    borderTopStartRadius: 2,
  },
  title: {
    fontSize: 22,
    alignSelf: 'center',
    fontWeight: 'bold',
    fontFamily: 'SourceSansPro',
  },
  blocos2: {
    height: 25,
    width: 345,
    borderWidth: 1,
    marginTop: 10,
    alignSelf: 'center',
    alignItems: 'center',
    backgroundColor: '#000',
    borderTopRightRadius: 2,
    borderTopLeftRadius: 2,
  },
  blocos: {
    fontSize: 16,
    color: '#fff',
    fontFamily: 'SourceSansPro',
  },
  texts: {
    alignSelf: 'flex-start',
    fontSize: 18,
    paddingHorizontal: 20,
    paddingVertical: 15,
    fontFamily: 'SourceSansPro',
  },
  input2: {
    flex: 1,
    backgroundColor: '#ffff',
    alignItems: 'center',
    justifyContent: 'center',
  },
  form: {
    alignSelf: 'stretch',
    paddingHorizontal: 8,
    marginTop: 5,
  },
  label: {
    fontWeight: 'bold',
    color: '#444',
    marginBottom: 8,
  },
  input: {
    borderWidth: 1,
    borderColor: '#ddd',
    paddingHorizontal: 20,
    fontSize: 16,
    color: '#444',
    height: 44,
    marginBottom: 20,
    borderRadius: 2,
  },
  butons: {
    alignSelf: 'center',
  },
  button: {
    height: 42,
    width: 345,
    backgroundColor: '#379e14',
    justifyContent: 'center',
    alignItems: 'center',
    borderRadius: 2,
  },
  buttonText: {
    color: '#000',
    fontWeight: 'bold',
    fontSize: 16,
  },
  buttonVisualize: {
    height: 42,
    width: 345,
    backgroundColor: '#ff0000',
    justifyContent: 'center',
    alignItems: 'center',
    marginTop: 10,
    borderRadius: 2,
  },
  modbus: {
    width: Dimensions.get('window').width * 0.8,
    height: 150,
  },
});

export default styles;
