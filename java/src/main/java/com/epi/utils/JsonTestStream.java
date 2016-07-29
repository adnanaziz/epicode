package com.epi.utils;

import javax.json.Json;
import javax.json.JsonArrayBuilder;
import javax.json.JsonObjectBuilder;

public class JsonTestStream implements AbstractTestStream {
  private static final String INPUT_TAG = "input";
  private static final String EXPECTED_OUTPUT_TAG = "expected_output";
  private static final String USER_OUTPUT_TAG = "user_output";
  private static final String STATUS_TAG = "status";
  private static final String MEASUREMENT_TAG = "measurement";
  private JsonObjectBuilder builder;
  private JsonArrayBuilder outerBlock;

  public JsonTestStream(JsonArrayBuilder outerBlock) {
    this.outerBlock = outerBlock;
  }

  @Override
  public void startTest(TestType type, String description) {
    builder = Json.createObjectBuilder();
    builder.add("description", description);
    builder.add("type", type.name().toLowerCase());
  }

  @Override
  public void endTest() {
    outerBlock.add(builder);
  }

  @Override
  public void registerInput(Object value) {
    JsonUniversalObjectWriter.handle(builder, INPUT_TAG, value);
  }

  @Override
  public void registerExpectedOutput(Object value) {
    JsonUniversalObjectWriter.handle(builder, EXPECTED_OUTPUT_TAG, value);
  }

  @Override
  public void registerUserOutput(Object value, boolean match) {
    builder.add(STATUS_TAG, match ? "ok" : "failed");
    JsonUniversalObjectWriter.handle(builder, USER_OUTPUT_TAG, value);
  }

  @Override
  public void registerUnhandledException() {
    builder.add(STATUS_TAG, "unhandled_exception");
    builder.addNull(USER_OUTPUT_TAG);
  }

  @Override
  public void registerNullPointerException() {
    builder.add(STATUS_TAG, "null_pointer_exception");
    builder.addNull(USER_OUTPUT_TAG);
  }

  @Override
  public void registerPerformanceTest(PerformanceMeasure m, AbstractTestOptions options) {
    builder.add(STATUS_TAG, m.succeeded(options) ? "ok" : "failed");
    builder.add(MEASUREMENT_TAG, Json.createObjectBuilder().
        add("limit", m.getLimit(options)).
        add("reference", m.getReferenceStopwatch().getMillis()).
        add("user", m.getUserStopwatch().getMillis()));
  }

  @Override
  public AbstractPairWriter getInputWriter() {
    return new JsonPairWriter(INPUT_TAG, builder);
  }

  @Override
  public AbstractPairWriter getExpectedOutputWriter() {
    return new JsonPairWriter(EXPECTED_OUTPUT_TAG, builder);
  }

  @Override
  public AbstractPairWriter getUserOutputWriter(boolean match) {
    builder.add(STATUS_TAG, match ? "ok" : "failed");
    return new JsonPairWriter(USER_OUTPUT_TAG, builder);
  }
}
