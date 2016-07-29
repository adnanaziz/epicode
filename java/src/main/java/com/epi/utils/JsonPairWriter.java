package com.epi.utils;

import javax.json.Json;
import javax.json.JsonObjectBuilder;

public class JsonPairWriter implements AbstractPairWriter {
  private JsonObjectBuilder builder;
  private JsonObjectBuilder outerBlock;
  private String blockName;

  public JsonPairWriter(String blockName, JsonObjectBuilder outerBlock) {
    this.outerBlock = outerBlock;
    this.blockName = blockName;
    builder = Json.createObjectBuilder();
  }

  @Override
  public AbstractPairWriter writePair(String name, Object value) {
    JsonUniversalObjectWriter.handle(builder, name, value);
    return this;
  }

  @Override
  public void close() {
    outerBlock.add(blockName, builder);
  }
}
