const fz = require('zigbee-herdsman-converters/converters/fromZigbee');
const tz = require('zigbee-herdsman-converters/converters/toZigbee');
const exposes = require('zigbee-herdsman-converters/lib/exposes');
const reporting = require('zigbee-herdsman-converters/lib/reporting');
const constants = require('zigbee-herdsman-converters/lib/constants');
const e = exposes.presets;
const ea = exposes.access;


const fzLocal = {
  rpm: {
    cluster: 'genMultistateOutput',
    type: ['attributeReport', 'readResponse'],
    convert: (model, msg, publish, options, meta) => {
      const rpm = msg.data['presentValue'];
      return { 'rpm': rpm };
    },
  }
}

const definition = {
  zigbeeModel: ['rack_out_of_dust'],
  model: 'rack_out_of_dust',
  vendor: 'VarOfLa',
  description: 'Automatically generated definition',
  exposes: [e.fan().withModes(['low', 'medium', 'high', 'auto']),
  e.numeric('rpm', ea.STATE).withLabel('RPM').withUnit('rpm').withDescription('Fan Speed in RPM'),
  e.pm10(), e.pm25(), e.temperature(), e.humidity()],
  fromZigbee: [fz.fan, fzLocal.rpm, fz.heiman_air_quality, fz.pm25, fz.temperature, fz.humidity],
  toZigbee: [tz.fan_mode],

  configure: async (device, coordinatorEndpoint) => {
    const endpoint = device.getEndpoint(1);
    await reporting.bind(endpoint, coordinatorEndpoint, ['genMultistateOutput', 'heimanSpecificAirQuality', 'pm25Measurement', 'msTemperatureMeasurement', 'msRelativeHumidity']);

    await reporting.temperature(endpoint, { min: 0, max: 3600, change: 1 });
    await reporting.humidity(endpoint, { min: 0, max: 3600, change: 1 });

    await endpoint.configureReporting('genMultistateOutput', reporting.payload('presentValue', 0, constants.repInterval.HOUR, 1));
    await endpoint.configureReporting('heimanSpecificAirQuality', reporting.payload('pm10measuredValue', 0, constants.repInterval.HOUR, 1));
    await endpoint.configureReporting('pm25Measurement', reporting.payload('measuredValue', 0, constants.repInterval.HOUR, 1));

  },
};

module.exports = definition;
