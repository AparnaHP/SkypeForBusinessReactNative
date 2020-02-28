import React, { Component } from "react";
import { View, Text, StyleSheet, TouchableHighlight,NativeModules } from "react-native";

export default class Flex extends Component {
  render() {
    return (

      <View style={styles.bgStyle}>
    
      <TouchableHighlight style={styles.buttonStyle} underlayColor="#009688"
              onPress={() => NativeModules.ActivityStarter.loadSkypeForBusiness("https://meet.lync.com/putyoururlhere","David Max")}>
            <Text style={styles.textStyle}>Join Meeting</Text>
      </TouchableHighlight> 
      </View>
    );
  }
}

const styles = StyleSheet.create({
  bgStyle: {
      justifyContent: 'center',
      alignItems: 'center',
      width: '100%',
      height: '100%'
      },

  buttonStyle: {
      justifyContent: 'center',
      alignItems: 'center',
      width: 160,
      height: 40,
      borderRadius:10,
      backgroundColor : '#009688',
      padding: 1
    },

  textStyle: {

      color: '#FFFFFF'
  }
        
});
